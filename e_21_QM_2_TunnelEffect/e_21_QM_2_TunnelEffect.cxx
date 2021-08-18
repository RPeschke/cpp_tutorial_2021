

#include "App.h"

#include <iostream>

#include <random>
#include <imgui_stdlib.h>
#include "TMath.h"

#include "wave_function.hh"
#include "qm_operators.hh"

#include "group_helper.hh"
#include "group_plot.hh"
#include "group_io.hh"
#include "group_joins.hh"


using namespace group_helper;

AXIS_NAME(Energy, double);

struct complex {
	constexpr complex(double r_, double i_=0) :r(r_), i(i_) {}
	double r, i;
	complex operator-() const{
		return { -r,-i };
	}
	complex operator!() const {
		return { r,-i };
	}
};

constexpr complex j = complex(0,1);

constexpr complex operator*(const complex& a, const complex& b) {
	return {
		a.r * b.r - a.i * b.i,
		a.r * b.i + a.i * b.r
	};
}

constexpr complex operator*(const complex& a, const double b) {
	return {
		a.r * b,
		a.i * b
	};
}

constexpr complex operator*(const double a, const complex& b) {
	return {
		a * b.r,
		a * b.i
	};
}

constexpr complex operator/(const complex& a, const complex& b) {
	
	double d = b.r * b.r + b.i * b.i;
	return {
		(a.r * b.r + a.i * b.i)/d,
		(a.i * b.r - a.r * b.i)/d
	};
}

constexpr complex operator/(const complex& a, const double b) {
	
	return a / complex(b);
	
}

constexpr complex operator/(const double a, const complex& b) {
	return complex( a) / b;
}

constexpr complex operator+(const complex& a, const complex& b) {
	return {
		a.r + b.r ,
		a.i + b.i 
	};
}

constexpr complex operator-(const complex& a, const complex& b) {
	return {
		a.r - b.r ,
		a.i - b.i
	};
}

complex exp(complex c) {
	return {
		TMath::Exp(c.r) * TMath::Cos(c.i),
		TMath::Exp(c.r) * TMath::Sin(c.i)
	};
}

constexpr double re(const complex& a) {
	return a.r;
}
constexpr double im(const complex& a) {
	return a.i;
}

complex sqrt(complex c) {
	double r = TMath::Sqrt( re( !c * c));
	double phi = TMath::ATan2(im(c), re(c))/2.0;

	return {
		r * TMath::Cos(phi),
		r * TMath::Sin(phi)
	};
}

template <typename AXIS_X, typename AXIS_Y, typename AXIS_Z>
struct ImGui_plotter {



	template <typename T1>
	void operator()(T1&& data, const char* name, const char* name1) {
		x2.clear();
		y2.clear();
		for (auto& e : data) {
			x2.push_back(AXIS_X(e));
			y2.push_back(AXIS_Y(e));
		}
		ImPlot::PlotLine(name, x2.data(), y2.data(), x2.size());

		x2.clear();
		y2.clear();
		for (auto& e : data) {
			x2.push_back(AXIS_X(e));
			y2.push_back(AXIS_Z(e));
		}
		ImPlot::PlotLine(name1, x2.data(), y2.data(), x2.size());
	}
	std::vector<double> x2, y2;
};



template <typename AXIS_X, typename AXIS_Y>
struct ImGui_plotter1 {



	template <typename T1>
	void operator()(T1&& data, const char* name) {
		x2.clear();
		y2.clear();
		for (auto& e : data) {
			x2.push_back(AXIS_X(e));
			y2.push_back(AXIS_Y(e));
		}
		ImPlot::PlotLine(name, x2.data(), y2.data(), x2.size());


	}
	std::vector<double> x2, y2;
};


auto make_wave_parameter_Energy_LT_0(double Energy, double V, double L) {

	auto k = sqrt(complex(Energy * 2));
	auto kappa = sqrt(complex(2 * (V - Energy)));
	// 	complex kappa = 0;
	// 	if (V - Energy > 0) {
	// 		kappa = complex( TMath::Sqrt(2 * (V - Energy)) );
	// 	}else {
	// 		kappa = complex(0, TMath::Sqrt(2 * ( Energy-V)));
	// 	}
	// 	


		//double L = { 0.5 };

	auto C = 0.5 * (1 + j * k / kappa) * exp(j * k * L) * exp(-kappa * L);
	auto D = 0.5 * (1 - j * k / kappa) * exp(j * k * L) * exp(kappa * L);
	auto A = 0.5 * (1 + kappa / (j * k)) * C + 0.5 * (1 - kappa / (j * k)) * D;
	auto B = 0.5 * (1 - kappa / (j * k)) * C + 0.5 * (1 + kappa / (j * k)) * D;

	auto F = TMath::Sqrt(1.0 / re((!A * A)));
	A = A * F;
	B = B * F;
	C = C * F;
	D = D * F;

	return  std::make_tuple(A, B, C, D, F, k, kappa);
}


auto make_wave_parameter(double Energy, double V, double L) {
	if (Energy>=0){
		return make_wave_parameter_Energy_LT_0(Energy,V,L);
	}

	auto k =  sqrt( complex(Energy * 2)) ;
	auto kappa =  sqrt(complex(2 * (V - Energy))) ;
// 	complex kappa = 0;
// 	if (V - Energy > 0) {
// 		kappa = complex( TMath::Sqrt(2 * (V - Energy)) );
// 	}else {
// 		kappa = complex(0, TMath::Sqrt(2 * ( Energy-V)));
// 	}
// 	
	
	
	//double L = { 0.5 };

	auto C = 0.5 * (1 + j * k / kappa) * exp(j * k * L) * exp(-kappa * L);
	auto D = 0.5 * (1 - j * k / kappa) * exp(j * k * L) * exp(kappa * L);
	auto B =  C +  D;
	
	
	auto A = complex(0);

	auto F = TMath::Sqrt(1.0 / re((!B * B)));
 	A = A * F;
	B = B * F;
 	C = C * F;
 	D = D * F;

	return  std::make_tuple( A, B, C, D, F, k, kappa );
}

auto make_wafevorm_psi0(double E, double V, double L) {

	let [A, B, C, D, F, k, kappa ]= make_wave_parameter(E, V, L);

	let x_r = x_range(-10, 10, 0.01);



	let psi0 = wave_function(fill_group_vector(x_r,
		[&](let& e) -> psi_real {
			let x1 = x_t(e);
			if (x1 <= 0) {
				return re(
					A * exp(j * x1 * k) + B * exp(-j * x1 * k)
				);
			}
			return 0;
		},
		[&](let& e) -> psi_img {
			let x1 = x_t(e);
			if (x1 <= 0) {
				return im(
					A * exp(j * x1 * k) + B * exp(-j * x1 * k)
				);
			}
			return 0;

		},
			[](let& e) -> x_t { return  x_t(e);  }
		));
	return psi0;
}



auto make_wafevorm_psi1(double E, double V, double L) {
	let[A, B, C, D, F, k, kappa] = make_wave_parameter(E, V, L);
	let x_r = x_range(-10, 10, 0.01);




	let psi1 = wave_function(fill_group_vector(x_r,
		[&](let& e) -> psi_real {
			let x1 = x_t(e);
			if (x1 > 0 && x1 <= L) {
				return re(
					C * exp(x1 * kappa) + D * exp(-x1 * kappa)
				);
			}
			return 0;
		},
		[&](let& e) -> psi_img {
			let x1 = x_t(e);
			if (x1 > 0 && x1 <= L) {
				return im(
					C * exp(x1 * kappa) + D * exp(-x1 * kappa)
				);
			}
			return 0;

		},
			[](let& e) -> x_t { return  x_t(e);  }
		));



	return psi1;
}



auto make_wafevorm_psi2(double E,double V, double L) {
	//double V(1);
	let[A, B, C, D, F, k, kappa] = make_wave_parameter(E, V, L);

	let x_r = x_range(-10, 10, 0.01);

	let psi2 = wave_function(fill_group_vector(x_r,
		[&](let& e) -> psi_real {
			let x1 = x_t(e);
			if (x1 > L) {
				return re(
					F*exp(j * x1 * k)
				);
			}
			return 0;
		},
		[&](let& e) -> psi_img {
			let x1 = x_t(e);
			if (x1 > L) {
				return im(
					F * exp(j * x1 * k)
				);
			}
			return 0;
		},
			[](let& e) -> x_t { return  x_t(e);  }
		));


	return psi2;
}


auto make_potential(double E , double V, double L) {



	let x_r = x_range(-10, 10, 0.01);

	let psi1 = wave_function(fill_group_vector(x_r,
		[&](let& e) -> psi_real {
			let x1 = x_t(e);
			if (x1 > 0 && x1 <= L) {
				return re(
					V
				);
			}
			return 0;
		},
		[&](let& e) -> psi_img {
			return E;

		},
			[](let& e) -> x_t { return  x_t(e);  }
		));

	return psi1;
}


void tunnel() {

	ImGui_plotter<x_t, psi_real, psi_img> pl1;
	std::vector<double> x2, y2;
	double Energy = 0.5;
	App desmos(640, 480, "ImDesmos Graphing Calculator",
		[&] {

			ImGui::Begin("ImDesmos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
			static float V_Width = 0.123f, V_Height = 1.f, Energy_= 0.5f;
			ImGui::SliderFloat("V Width", &V_Width, 0.0f, 5.0f, "ratio = %.3f");
			ImGui::SliderFloat("V Height", &V_Height, -5.0f, 5.0f, "ratio = %.3f");
			ImGui::SliderFloat("Energy_", &Energy_, -5.0f, 5.0f, "ratio = %.3f");
			static bool show_pdf = false;
			ImGui::Checkbox("show PDF", &show_pdf);
			let psi0 = make_wafevorm_psi0(Energy_, V_Height, V_Width);
			let psi1 = make_wafevorm_psi1(Energy_, V_Height, V_Width);
			let psi2 = make_wafevorm_psi2(Energy_, V_Height, V_Width);
			let V = make_potential(Energy_, V_Height, V_Width);
			ImPlot::SetNextPlotLimitsX(-5, 5);
			ImPlot::SetNextPlotLimitsY(-1, 4);
			if (show_pdf){

				static float ratios[] = { 1,1 };
				if (ImPlot::BeginSubplots("##Stocks", 2, 1, ImVec2(-1, -1), ImPlotSubplotFlags_LinkCols, ratios)) {
					if (ImPlot::BeginPlot("##Plot1", "x", "y", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
						auto limits = ImPlot::GetPlotLimits();

						pl1(psi0, "psi0_re", "psi0_im");
						pl1(psi1, "psi1_re", "psi1_im");
						pl1(psi2, "psi2_re", "psi2_im");
						pl1(V, "V", "E");
						ImPlot::EndPlot();
					}
					if (ImPlot::BeginPlot("##Plot2", "x", "y", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
						auto limits = ImPlot::GetPlotLimits();

						pl1(!psi0 * psi0, "psi0_re", "psi0_im");
						pl1(!psi1 * psi1, "psi1_re", "psi1_im");
						pl1(!psi2 * psi2, "psi2_re", "psi2_im");
						pl1(V, "V", "E");
						ImPlot::EndPlot();
					}
					ImPlot::EndSubplots();
				}
			} else {
				if (ImPlot::BeginPlot("##Plot1", "x", "y", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
					auto limits = ImPlot::GetPlotLimits();

					pl1(psi0, "psi0_re", "psi0_im");
					pl1(psi1, "psi1_re", "psi1_im");
					pl1(psi2, "psi2_re", "psi2_im");
					pl1(V, "V", "E");
					ImPlot::EndPlot();
				}
			}
			ImGui::SameLine();

			ImGui::End();
		});
	desmos.run();
}



int main(int argc, char const* argv[])
{
	tunnel();

	return 0;
}

