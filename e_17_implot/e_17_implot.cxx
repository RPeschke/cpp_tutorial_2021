
#include "App.h"

#include <iostream>
#include <imgui_stdlib.h>
#include "TMath.h"


template <typename T>
static inline T remap(T x, T x0, T x1, T y0, T y1) { return y0 + (x - x0) * (y1 - y0) / (x1 - x0); }


int main(int argc, char const* argv[])
{

	App desmos(640, 480, "ImDesmos Graphing Calculator",
		[&]() {


		ImGui::Begin("ImDesmos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);


		ImGui::SameLine();


		if (ImPlot::BeginPlot("##Plot", "time", "space", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
			auto limits = ImPlot::GetPlotLimits();

				//ImPlot::SetNextLineStyle(pl.color);

			constexpr int size_of_data = 10000; 
			{


				double x[size_of_data] = { 0 };
				double y[size_of_data] = { 0 };
				for (int i = 0; i < size_of_data; ++i) {
					x[i] = remap((double)i, 0.0, (double)(size_of_data - 1), limits.X.Min, limits.X.Max);
					y[i] = TMath::Sin(x[i])*2;
				}

				ImPlot::PlotLine("plot1", x, y, size_of_data);
			}
			{
				double x[size_of_data] = { 0 };
				double y[size_of_data] = { 0 };
				for (int i = 0; i < size_of_data; ++i) {
					x[i] = remap((double)i, 0.0, (double)(size_of_data - 1), -100.0, 100.0);
					y[i] = TMath::Cos(x[i]);
				}

				ImPlot::PlotLine("plot2", x, y, size_of_data); }
			ImPlot::EndPlot();
		}
		ImGui::End();
	});
	desmos.run();
	return 0;
}
