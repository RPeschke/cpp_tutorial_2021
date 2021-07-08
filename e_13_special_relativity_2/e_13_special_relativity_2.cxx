

#include "TGSignals.hh"


#include "TImage.h"
#include "TApplication.h"
#include <iostream>
#include "group_helper.hh"
#include "group_plot.hh"
#include "group_io.hh"
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

using df_objects = data_frame<Object_ID, df_time, x_t, y_t>;

using TGraph_sp = std::shared_ptr<TGraph>;


using position_2d = std::tuple<x_t, y_t>;
using velocity_2d = std::tuple<v_x_t, v_y_t>;


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

	for ( auto e: t){
		if (f(e)) {
			ret.push_back (e);
		}
	}

	return ret;
}

int g_ring_index = 1000;

struct expanding_ring {

	position_2d m_center;
	position_2d m_current_center;
	velocity_2d m_velovitiy;
	TGraph_sp graphs;
	TGraph_sp m_center_marker;

	df_objects m_data;
	df_objects center_point;
	double start_time = 0;

	int ring_index ;
	data_frame< Angle>df0 = fill_vector1(100, [&](auto index) -> Angle { return index / 100.0 * 2.0 * TMath::Pi(); });
	double  Velocity = 0.5;
	double last_distance_to_point = 1e30;

	template<typename T, typename T1>
	expanding_ring(const T& t, const T1& t1, double Velocity_Ring) {
		m_center = std::make_tuple(x_t(t), y_t(t));
		m_velovitiy = std::make_tuple(v_x_t(t1), v_y_t(t1));
		Velocity = Velocity_Ring;

		ring_index = g_ring_index;
		g_ring_index += 1000;
	}

	template <typename T>
	bool is_hit(const T& vec) {
		bool ret = false;
		if (start_time > 0) return ret;
		auto current_distance_to_point_1 = min_distance<x_t, y_t>(vec, m_current_center);
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



	void update(double time_index) {
		center_point.clear();
		m_data.clear();
		center_point.emplace_back(
			ring_index,
			time_index,
			x_t(m_center) + v_x_t(m_velovitiy) * time_index,
			y_t(m_center) + v_y_t(m_velovitiy) * time_index
		);
		m_current_center = std::make_tuple(x_t(m_center) + v_x_t(m_velovitiy) * time_index, y_t(m_center) + v_y_t(m_velovitiy) * time_index);
		if (start_time == 0) {
			return;
		}

		std::tuple<x_t, y_t> center_start = std::make_tuple(x_t(m_center) + v_x_t(m_velovitiy) * start_time, y_t(m_center) + v_y_t(m_velovitiy) * start_time);
		int i = 0;
		m_data = fill_vector(df0,
			[&](let& e) -> Object_ID { return ring_index + (++i); },
			[&](let& e) -> df_time { return time_index; },
			[&](let& e) -> x_t { return x_t(center_start) + Velocity * (time_index - start_time) * TMath::Cos(Angle(e)); },
			[&](let& e) -> y_t { return y_t(center_start) + Velocity * (time_index - start_time) * TMath::Sin(Angle(e)); }

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

df_objects create_dataset(double SignalVelocity , double ObserverVelocity, double max_time = 100) {
	df_objects ret;
	

	expanding_ring moving_point_A{
		std::make_tuple(x_t(0), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};
	moving_point_A.start(0.1);
	expanding_ring moving_point_B{
		std::make_tuple(x_t(5), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};
	double time_index = 0;
	const int frameTime_in_ms = 100;

	while (time_index < max_time) {
		time_index += frameTime_in_ms / 1000.0;
		moving_point_A.update(time_index);
		moving_point_B.update(time_index);
		if (moving_point_B.is_hit(moving_point_A.m_data)) {
			moving_point_B.start(time_index);
			moving_point_A.stop();
			ret.emplace_back(
				1200,
				time_index,
				x_t(moving_point_B.center_point[0]),
				y_t(moving_point_B.center_point[0])
			);
		}
		if (moving_point_A.is_hit(moving_point_B.m_data)) {
			moving_point_A.start(time_index);
			moving_point_B.stop();
			ret.emplace_back(
				2200,
				time_index,
				x_t(moving_point_A.center_point[0]),
				y_t(moving_point_A.center_point[0])
			);
		}

		ret.insert(ret.end(), moving_point_A.m_data.begin(), moving_point_A.m_data.end());
		ret.insert(ret.end(), moving_point_B.m_data.begin(), moving_point_B.m_data.end());

		ret.insert(ret.end(), moving_point_A.center_point.begin(), moving_point_A.center_point.end());
		ret.insert(ret.end(), moving_point_B.center_point.begin(), moving_point_B.center_point.end());
	}
	std::sort(ret.begin(), ret.end());
	return ret;
}




template <typename T>
auto lorenz_boost(const T& vec,const  double Velocity) {
	const double observer_gammer = 1.0 / TMath::Sqrt(1 - Velocity * Velocity);
	return fill_vector(vec,
		[&](let& e) -> Object_ID { return Object_ID(e); },
		[&](let& e) -> df_time { return observer_gammer*(df_time(e) - Velocity* x_t(e)); },
		[&](let& e) -> x_t { return observer_gammer*(x_t(e) - Velocity* df_time(e)); },
		[&](let& e) -> y_t { return y_t(e); },
		[&](let& e) -> time_boost_t { return (double) df_time(e); },
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


std::tuple< TCanvas*, TGraph_sp> make_canvas() {
	TCanvas* c1 = new TCanvas("c", "", 500, 500);
	c1->SetFixedAspectRatio();
	data_frame<x_t, y_t> range;
	double x = 10;
	range.emplace_back(50, x);
	range.emplace_back(x, -x);
	range.emplace_back(-x, -x);
	range.emplace_back(-x, x);

	auto g = to_TGraph<x_t, y_t>(range);

	g->Draw("A*");

	return { c1 , g };
}


df_objects create_Michelson_Morley_dataset(double SignalVelocity, double ObserverVelocity, double max_time = 100) {
	df_objects ret;


	expanding_ring center_to_A{
		std::make_tuple(x_t(0), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};
	center_to_A.start(0.1);
	expanding_ring center_to_B{
		std::make_tuple(x_t(0), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};
	center_to_B.start(0.1);



	expanding_ring point_A{
		std::make_tuple(x_t(5), y_t(0)),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};

	expanding_ring point_B{
		std::make_tuple(x_t(0), y_t(5 / TMath::Sqrt(1- ObserverVelocity*ObserverVelocity) )),
		std::make_tuple(v_x_t(ObserverVelocity) , v_y_t(0)),
		SignalVelocity
	};



	double time_index = 0;
	const int frameTime_in_ms = 100;

	while (time_index < max_time) {
		time_index += frameTime_in_ms / 1000.0;
		center_to_A.update(time_index);
		center_to_B.update(time_index);
		point_A.update(time_index);
		point_B.update(time_index);




		if (point_A.is_hit(center_to_A.m_data)) {
			point_A.start(time_index);
			center_to_A.stop();
			ret.emplace_back(
				1200,
				time_index,
				x_t(point_A.center_point[0]),
				y_t(point_A.center_point[0])
			);
		}
		if (center_to_A.is_hit(point_A.m_data)) {
			center_to_A.start(time_index);
			point_A.stop();
			ret.emplace_back(
				2200,
				time_index,
				x_t(center_to_A.center_point[0]),
				y_t(center_to_A.center_point[0])
			);
		}

		if (point_B.is_hit(center_to_B.m_data)) {
			point_B.start(time_index);
			center_to_B.stop();
			ret.emplace_back(
				3200,
				time_index,
				x_t(point_B.center_point[0]),
				y_t(point_B.center_point[0])
			);
		}
		if (center_to_B.is_hit(point_B.m_data)) {
			center_to_B.start(time_index);
			point_B.stop();
			ret.emplace_back(
				4200,
				time_index,
				x_t(center_to_B.center_point[0]),
				y_t(center_to_B.center_point[0])
			);
		}



		ret.insert(ret.end(), point_A.m_data.begin(), point_A.m_data.end());
		ret.insert(ret.end(), point_B.m_data.begin(), point_B.m_data.end());

		ret.insert(ret.end(), center_to_A.m_data.begin(), center_to_A.m_data.end());
		ret.insert(ret.end(), center_to_B.m_data.begin(), center_to_B.m_data.end());

		ret.insert(ret.end(), point_A.center_point.begin(), point_A.center_point.end());
		ret.insert(ret.end(), point_B.center_point.begin(), point_B.center_point.end());

		ret.insert(ret.end(), center_to_A.center_point.begin(), center_to_A.center_point.end());
		ret.insert(ret.end(), center_to_B.center_point.begin(), center_to_B.center_point.end());
	}
	std::sort(ret.begin(), ret.end());
	return ret;

}

struct to_pair
{
	template<typename T1, typename T2>
	constexpr auto operator()(T1&& t1, T2&& t2) const noexcept
	{
		return std::make_pair(t1, t2);
	}
};

struct to_tuple
{
	template<typename T1, typename T2>
	constexpr auto operator()(T1&& t1, T2&& t2) const noexcept
	{
		return std::make_tuple(t1, t2);
	}
};

template <typename T1, typename T2, typename projecttion_t = to_pair>
auto vec_zip(const T1& t1, const  T2& t2, projecttion_t project = to_pair()) {

	std::vector<  decltype(project(*t1.begin(), *t2.begin()))  > ret;

	auto t1_itt = t1.begin();
	auto t2_itt = t2.begin();
	while (t1_itt != t1.end() && t2_itt != t2.end()) {
		ret.push_back(project(*t1_itt, *t2_itt));
		++t1_itt;
		++t2_itt;
	}
	return ret;

}

template <typename T> 
struct is_same {
	T m_t;
	is_same(T t) :m_t(t) {}
	template <typename T1>
	bool operator()(const T1& e) {
		return m_t == e;
	}
};

int main(int argc, char** argv) {
	TApplication app("myApp", &argc, argv);
	auto [c1, g] = make_canvas();

	const double signalVelocity =1;
	const double ObserverVelocity = 0.4;
	auto df = create_Michelson_Morley_dataset(signalVelocity, ObserverVelocity,100);


	auto df_boost = lorenz_boost(df, ObserverVelocity);
	std::string FileName = "test.root";
	save(FileName, df, "df");
	save(FileName, df_boost, "df_boost", "update");



	auto hit_zero_for_A = filter(df_boost, is_same(Object_ID(2200))); 

	auto hit_zero_for_B = filter(df_boost, is_same(Object_ID(4200))); 

	auto hits = vec_zip(hit_zero_for_A, hit_zero_for_B, to_pair()); 



	save(FileName, hits, "hits", "update");
	double time_index = 0;
	const int frameTime_in_ms = 100;

	std::vector<std::shared_ptr<TGraph>> graphs;

	TTimer timer = TTimer(frameTime_in_ms);
	RQ_signals(timer).Timeout([&]() {
		graphs.clear();
		time_index += frameTime_in_ms / 1000.0;

		auto df1 = group<Object_ID>::apply2(df,

			[&](auto InRange) {
			return   interpolate<df_time, x_t, y_t>::apply(InRange, df_time(time_index));
		}
		);
		//auto df1 = interpolate<df_time, x_t, y_t>::apply(df, time_index);
	
		auto g1 = ::plot<x_t, y_t>(df1, "same*");
		

		c1->Modified();
		c1->Update();
	});

	timer.TurnOn();
	app.Run();
}