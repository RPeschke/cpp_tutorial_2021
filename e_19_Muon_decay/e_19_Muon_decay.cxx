#include "decay_lib/Particles.hh"


#include "App.h"

#include <iostream>

#include <random>
#include <imgui_stdlib.h>
#include "TMath.h"






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


template <typename T>
auto fold(T&& t) {
	return [t](auto& container) {
		for (auto& e : container) {
			t(e);
		}
	};
}


int main(int argc, char const* argv[])
{

	df_objects df;

	std::vector<std::shared_ptr<Particle_base>> particles{
		make_pion(1, 1e9, 0, 0)


	};
	std::vector<std::shared_ptr<Particle_base>> new_particles;
	
	double t = 0;
	while (t < 1e-4){
		new_particles.clear();
		t += 1e-8;
		fold([&](auto& e) {
			e->updata(t);
			if (e->isDecayed()) {
				auto d = e->Decayed_product();
				new_particles.insert(new_particles.end(), d.begin(), d.end());
			}
		})(particles);
			

		particles.insert(particles.end(), new_particles.begin(), new_particles.end());
		particles.erase(std::remove_if(particles.begin(), particles.end(), [](const auto& e) {return e->isDecayed(); }), particles.end());

		fold([&](auto& e) {
			let f_position = e->getCoordinates();
			df.push_back(f_position);
		})(particles);

	}

	std::string FileName = "test.root";
	save(FileName, df, "df");
	double time_index = 0;
	const double frameTime_in_ms = 1000e6;
	clock_t t_last = clock();
	clock_t t_now = clock();
	std::vector<double> x(df.size()), y(df.size());
	std::vector<double> e_x(df.size()), e_y(df.size());
	std::vector<double> n_x(df.size()), n_y(df.size());
	std::vector<double> x4(df.size()), y4(df.size());
	std::vector<double> x5(df.size()), y5(df.size());
	std::vector<double> x6(df.size()), y6(df.size());
	//std::vector<double> x1, y1;

	App desmos(640, 480, "ImDesmos Graphing Calculator",
	[&]{
			t_now = clock();
			auto t_delta = t_now - t_last;
			t_last = t_now;
			time_index += t_delta / frameTime_in_ms;


			ImGui::Begin("ImDesmos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

			ImPlot::SetNextPlotLimitsX(-2e-6, 1e-5);
			ImPlot::SetNextPlotLimitsY(-5e-6, 5e-6);
			if (ImPlot::BeginPlot("##Plot", "x", "y", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
				auto limits = ImPlot::GetPlotLimits();

				//ImPlot::SetNextLineStyle(pl.color);

				




				x.clear();
				y.clear();

				e_x.clear();
				e_y.clear();

				n_x.clear();
				n_y.clear();

				x4.clear();
				y4.clear();


				x5.clear();
				y5.clear();


				x6.clear();
				y6.clear();



				for (let& e : df) {
					if (df_time(e)>time_index){
						continue;
					}
					if (Object_ID(e) == 1) {
						x.push_back(x_t(e));
						y.push_back(y_t(e));
					}

					if (Object_ID(e) == 2) {
						e_x.push_back(x_t(e));
						e_y.push_back(y_t(e));
					}
					if (Object_ID(e) == 3) {
						n_x.push_back(x_t(e));
						n_y.push_back(y_t(e));
					}
					if (Object_ID(e) == 4) {
						x4.push_back(x_t(e));
						y4.push_back(y_t(e));
					}

					

					if (Object_ID(e) == 5) {
						x5.push_back(x_t(e));
						y5.push_back(y_t(e));
					}


					if (Object_ID(e) == 6) {
						x6.push_back(x_t(e));
						y6.push_back(y_t(e));
					}
				}
				
				ImPlot::PlotScatter("Pion", x.data(), y.data(), x.size());








				ImPlot::PlotScatter("Muon", e_x.data(), e_y.data(), e_y.size());





				ImPlot::PlotScatter("Muon Anti Neutrino", n_x.data(), n_y.data(), n_y.size());




				
				ImPlot::PlotScatter("electron", x4.data(), y4.data(), y4.size());


				ImPlot::PlotScatter("Electron Anti Neutrino", x5.data(), y5.data(), y5.size());


				ImPlot::PlotScatter("Muon Neutrino", x6.data(), y6.data(), y6.size());

				ImPlot::EndPlot();
			}


			ImGui::SameLine();

			ImGui::End();
	});
	desmos.run();
	return 0;
}
