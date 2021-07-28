
#include "App.h"

#include <iostream>
#include <imgui_stdlib.h>
#include "TMath.h"


template <typename T>
static inline T remap(T x, T x0, T x1, T y0, T y1) { return y0 + (x - x0) * (y1 - y0) / (x1 - x0); }




#include "TGSignals.hh"


#include "TImage.h"
#include "TApplication.h"
#include <iostream>
#include "group_helper.hh"
#include "group_plot.hh"
#include "group_io.hh"
#include "group_joins.hh"

#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TBrowser.h"
#include "TTimer.h"
#include "TGraph.h"
#include "TMarker.h"

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include "TMath.h"
#include <bitset>
#include <memory>
#include <optional>
#include <span>

#include "group_optional_range.hh"

#define let  const auto
using namespace group_helper;
AXIS_NAME(x_t, double);
AXIS_NAME(y_t, double);
AXIS_NAME(v_x_t, double);
AXIS_NAME(v_y_t, double);
AXIS_NAME(df_time, double);
AXIS_NAME(Object_ID, int);
AXIS_NAME(Angle, double);


AXIS_NAME(x_boost_t, double);
AXIS_NAME(y_boost_t, double);
AXIS_NAME(time_boost_t, double);



template <typename... T>
using data_frame = std::vector<std::tuple<T...>>;

using df_objects_old = data_frame<Object_ID, df_time, x_t, y_t>;

using df_objects = group_vector<Object_ID, df_time, x_t, y_t>;

using TGraph_sp = std::shared_ptr<TGraph>;


using position_2d = std::tuple<x_t, y_t>;
using velocity_2d = std::tuple<v_x_t, v_y_t>;

const int Observers_a_index = 1e6;
const int Observers_b_index = 2e6;


template <typename XAxis_t, typename YAxis_t, typename VEC_t, typename Point_T>
auto min_distance(const VEC_t& vec, const Point_T& point) {
	double ret = 1e30;

	for (let& e : vec) {
		ret = std::min(ret, TMath::Power(XAxis_t(e) - XAxis_t(point), 2) + TMath::Power(YAxis_t(e) - YAxis_t(point), 2));
	}
	return ret;
}


template <typename T, typename F_T>
auto filter(const std::vector<T>& t, F_T&& f) {
	std::vector<T> ret;

	for (auto e : t) {
		if (f(e)) {
			ret.push_back(e);
		}
	}

	return ret;
}



struct expanding_ring {

	static int get_index() {
		static int g_ring_index = 1000;
		return g_ring_index++;
	}
	enum {
		idle,
		expanding,
		done
	} m_state = idle;

	position_2d m_center;
	//position_2d m_current_center;
	std::tuple<Object_ID, df_time, x_t, y_t> m_current_center;
	std::tuple<Object_ID, df_time, x_t, y_t> m_start_center;
	velocity_2d m_velovitiy;
	TGraph_sp graphs;
	TGraph_sp m_center_marker;

	df_objects_old m_data;
	df_objects_old center_point;
	double start_time = 0;

	int ring_index;
	data_frame< Angle>df0;
	double  Velocity = 0.5;
	double last_distance_to_point = 1e30;

	template<typename T, typename T1>
	expanding_ring(const T& t, const T1& t1, double Velocity_Ring, double starting_time_ = 0, int Ring_index = 0, double angle_ = 0) : start_time(starting_time_) {
		m_center = std::make_tuple(x_t(t), y_t(t));
		m_velovitiy = std::make_tuple(v_x_t(t1), v_y_t(t1));
		Velocity = Velocity_Ring;
		df0 = fill_vector1(1, [&](auto index) -> Angle { return angle_; });
		ring_index = Ring_index;
		m_current_center = std::make_tuple(ring_index, 0, x_t(t), y_t(t));;

	}

	template <typename T>
	bool is_hit(const T& point) {
		bool ret = false;
		if (start_time == 0) return ret;
		if (m_data.empty()) return false;

		auto current_distance_to_point_1 = min_distance<x_t, y_t>(m_data, point.m_current_center);

		if (last_distance_to_point < current_distance_to_point_1) {
			ret = true;
		}
		last_distance_to_point = current_distance_to_point_1;
		return ret;
	}


	void start(double time) {
		start_time = time;
	}



	void stop() {
		start_time = 0;
		m_data.clear();
		graphs.reset();

		last_distance_to_point = 1e30;
	}



	void update(double time_index, double delta_time) {

		center_point.clear();
		m_data.clear();
		center_point.emplace_back(
			ring_index,
			time_index,
			x_t(m_current_center) + v_x_t(m_velovitiy) * delta_time,
			y_t(m_current_center) + v_y_t(m_velovitiy) * delta_time
		);
		m_current_center = std::make_tuple(ring_index, time_index, x_t(m_current_center) + v_x_t(m_velovitiy) * delta_time, y_t(m_current_center) + v_y_t(m_velovitiy) * delta_time);
		if (time_index < start_time) {
			return;
		}
		if (start_time == 0) {
			return;
		}
		if (m_state == idle) {
			m_state = expanding;
			m_start_center = m_current_center;
		}


		int i = 0;
		m_data = fill_vector(df0,
			[&](let& e) -> Object_ID { return ring_index + (++i); },
			[&](let& e) -> df_time { return time_index; },
			[&](let& e) -> x_t { return x_t(m_start_center) + Velocity * (time_index - start_time) * TMath::Cos(Angle(e)); },
			[&](let& e) -> y_t { return y_t(m_start_center) + Velocity * (time_index - start_time) * TMath::Sin(Angle(e)); }

		);

	}
	TGraph* plot() {

		m_center_marker = ::plot<x_t, y_t>(center_point, "same*");
		if (start_time == 0) {
			return {};
		}

		graphs = ::plot<x_t, y_t>(m_data, "sameC");
		return graphs.get();
	}

};

df_objects create_dataset(double SignalVelocity, double ObserverVelocity, double max_time = 100) {
	std::shared_ptr<df_objects_old> ret = std::make_shared<df_objects_old>();
	std::vector< expanding_ring> stationary_sender_to_A;
	std::vector< expanding_ring> stationary_sender_to_B;


	for (int i = 0; i < 20; ++i) {
		stationary_sender_to_A.push_back(
			expanding_ring(
				std::make_tuple(x_t(0), y_t(0)),
				std::make_tuple(v_x_t(0), v_y_t(0)),
				SignalVelocity,
				(10. + 10.0 * i),
				Observers_a_index + 1 + i,
				TMath::Pi()
			)
		);
		stationary_sender_to_B.push_back(
			expanding_ring(
				std::make_tuple(x_t(0), y_t(0)),
				std::make_tuple(v_x_t(0), v_y_t(0)),
				SignalVelocity,
				(10. + 10.0 * i),
				Observers_b_index + 1 + i,
				0
			)
		);


	}


	expanding_ring moving_point_A{
		std::make_tuple(x_t(-40), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity,
		{},
		Observers_a_index

	};

	expanding_ring moving_point_B{
		std::make_tuple(x_t(10), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity,
		{},
		Observers_b_index
	};

	double time_index = 0;
	const double frameTime_in_ms = 100;

	while (time_index < max_time) {

		time_index += frameTime_in_ms / 1000.0;
		moving_point_A.update(time_index, frameTime_in_ms / 1000.0);
		ret->insert(ret->end(), moving_point_A.center_point.begin(), moving_point_A.center_point.end());


		moving_point_B.update(time_index, frameTime_in_ms / 1000.0);
		ret->insert(ret->end(), moving_point_B.center_point.begin(), moving_point_B.center_point.end());

		for (auto& e : stationary_sender_to_A) {

			e.update(time_index, frameTime_in_ms / 1000.0);
			ret->insert(ret->end(), e.m_data.begin(), e.m_data.end());

			if (e.is_hit(moving_point_A)) {
				e.stop();
				ret->emplace_back(
					1200,
					time_index,
					x_t(moving_point_A.center_point[0]),
					y_t(moving_point_A.center_point[0])
				);
			}
		}
		for (auto& e : stationary_sender_to_B) {
			e.update(time_index, frameTime_in_ms / 1000.0);
			ret->insert(ret->end(), e.m_data.begin(), e.m_data.end());

			if (e.is_hit(moving_point_B)) {
				e.stop();
				ret->emplace_back(
					2200,
					time_index,
					x_t(moving_point_B.center_point[0]),
					y_t(moving_point_B.center_point[0])
				);
			}
		}


	}
	std::sort(ret->begin(), ret->end());
	return ret;
}




template <typename T>
auto lorenz_boost(const T& vec, const  double Velocity) {
	const double observer_gammer = 1.0 / TMath::Sqrt(1 - Velocity * Velocity);
	return fill_group_vector(vec,
		[&](let& e) -> Object_ID { return Object_ID(e); },
		[&](let& e) -> df_time { return observer_gammer * (df_time(e) - Velocity * x_t(e)); },
		[&](let& e) -> x_t { return observer_gammer * (x_t(e) - Velocity * df_time(e)); },
		[&](let& e) -> y_t { return y_t(e); },
		[&](let& e) -> time_boost_t { return (double)df_time(e); },
		[&](let& e) -> x_boost_t { return (double)x_t(e); },
		[&](let& e) -> y_boost_t { return (double)y_t(e); }

	);
}



template <typename... AXIS_T>
struct interpolate {

	template <typename T0, typename T1, typename T>
	static auto interpolate_element(const T& e, const T& last, double time) {
		return (T0(e) - T0(last)) / (T1(e) - T1(last)) * (time - T1(last)) + T0(last);
	}

	template <typename T, typename T2>
	static auto apply(const T& vec, const T2& time) {
		std::tuple<AXIS_T...> ret;
		std::remove_cvref_t< decltype(*vec.begin())> last{};
		bool isvalid = false;
		for (const auto& e : vec) {
			if (TMath::Abs(T2(e) - time) > 0.3) {
				continue;
			}
			if ((T2(e) - time) * (T2(last) - time) <= 0 && isvalid) {

				ret = std::make_tuple(
					interpolate_element<AXIS_T, T2>(e, last, time)...
				);
				break;
			}
			isvalid = true;
			last = e;
		}
		return ret;
	}




};





int main(int argc, char const* argv[])
{
	const double signalVelocity = 1;
	const double ObserverVelocity = 2.0 / 5;

	auto df = create_dataset(signalVelocity, ObserverVelocity, 100);


	auto df_boost = lorenz_boost(df, ObserverVelocity);
	//auto df1_boost = make_group_vector(df_boost);
	std::string FileName = "test.root";
	save(FileName, df, "df");
	save(FileName, df_boost, "df_boost", "update");

	double time_index = 0;
	const int frameTime_in_ms = 500;
	std::vector<double> x, y;
	std::vector<double> x1, y1;

	clock_t t_last=  clock();
	clock_t t_now = clock();
	App desmos(640, 480, "ImDesmos Graphing Calculator",
		[&]() {

		t_now = clock();
		auto t_delta = t_now - t_last;
		t_last = t_now;
		time_index += t_delta / 500.0;


		ImGui::Begin("ImDesmos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
		
		ImPlot::SetNextPlotLimitsX(-50, 30);
		ImPlot::SetNextPlotLimitsY(-10, 60);
		if (ImPlot::BeginPlot("##Plot", "time", "space", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
			auto limits = ImPlot::GetPlotLimits();

			//ImPlot::SetNextLineStyle(pl.color);

			auto df1 = group<Object_ID>::apply2(df,
				[&](auto InRange) {
				auto ret = interpolate<df_time, x_t, y_t>::apply(InRange, df_time(time_index));
				return   ret;
			}
			);

			auto df2 = df[df.df_time() < time_index];




			x.clear();
			y.clear();

			for (let& e : df2) {
				x.push_back(x_t(e));
				y.push_back(df_time(e));
			}

			ImPlot::PlotScatter("plot1", x.data(), y.data(), x.size());


			auto df3 = df1[df1.Object_ID() == 1000000];



			x1.clear();
			y1.clear();
			for (let& e : df1) {
				x1.push_back(x_t(e));
				y1.push_back(df_time(e));

			}

			ImPlot::PlotScatter("plot2", x1.data(), y1.data(), x1.size());

			ImPlot::EndPlot();
		}

	
		ImGui::SameLine();
		
		ImGui::End();
	});
	desmos.run();
	return 0;
}
