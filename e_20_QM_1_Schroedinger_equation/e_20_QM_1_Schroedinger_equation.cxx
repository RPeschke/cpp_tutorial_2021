

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



AXIS_NAME(Energy, double);
using namespace group_helper;



class qm_operators1 {
	std::function<wave_function_e(const wave_function_e&)> m_op;
public:

	qm_operators1(std::function<wave_function_e(const wave_function_e&)>  op) :m_op(std::move(op)) {}






	auto operator*(const wave_function& wf) const {

		auto ret = fill_group_vector2(wf.m_data,
			m_op
		);
		return ret;
	}


	auto operator*(const qm_operators1& op) const {

		return qm_operators1(
			[m_op = this->m_op, op](const wave_function_e& e) -> wave_function_e {
				return m_op(op.m_op(e));
			}
		);
		
	}

};






qm_operators x = qm_operators(
	[](const wave_function& wf) {
		wave_function ret(

			fill_group_vector(wf.m_data,
				[](let& e) ->psi_real { return x_t(e)* psi_real(e);  },
				[](let& e) ->psi_img { return x_t(e) * psi_img(e);  },
				[](let& e) ->x_t { return x_t(e);  }
			)
		);


		return ret;
	});

qm_operators x_2 = qm_operators(
	[](const wave_function& wf) {
		return wave_function(
			fill_group_vector(wf.m_data,
				[&](let& e) ->psi_real { return x_t(e) * x_t(e) * psi_real(e);  },
				[&](let& e) ->psi_img { return x_t(e) * x_t(e) * psi_img(e);  },
				[](let& e) ->x_t { return x_t(e);  }
			)
		);

	});


qm_operators p = qm_operators(
	[](const wave_function& wf) {
		wave_function ret(

			fill_group_vector(wf.m_data,

				[&, old_psi = double(0), old_x = double(-1000)](let& e) mutable->psi_real {
			let ret = (psi_img(e) - old_psi) / (x_t(e) - old_x);
			old_psi = psi_img(e);
			old_x = x_t(e);
			return ret;
		},

				[&, old_psi = double(0), old_x = double(-1000)](let& e) mutable ->psi_img  {
			let ret = - (psi_real(e) - old_psi)/( x_t(e) - old_x);
			old_psi = psi_real(e);
			old_x = x_t(e);
			return ret;
		
		},

				[](let& e) ->x_t { return x_t(e);  }
			)
		);


		return ret;
	});

template <typename AXIS_X, typename AXIS_Y>
struct ImGui_plotter{


	
	template <typename T1>
	void operator()(T1&& data, const char * name) {
		x2.clear();
		y2.clear();
		for (auto & e :data.m_data ){
			x2.push_back(AXIS_X(e));
			y2.push_back(AXIS_Y(e));
		}
		ImPlot::PlotLine(name, x2.data(), y2.data(), x2.size());
		
	}
	std::vector<double> x2, y2;
};



wave_function get_psi_0() {
	return wave_function(fill_group_vector(200,
		[](let& e) -> psi_real {
			let x = -10 + e * 0.1;
			return  TMath::Power((1 / TMath::Pi()), 1.0 / 4.0) * TMath::Exp(-(x * x / 2));
		},
		[](let& e) -> psi_img { return 0;  },
			[](let& e) -> x_t { return  -10 + e * 0.1;  }
		));
}


wave_function get_psi_1() {
	return wave_function(fill_group_vector(200,
		[](let& e) -> psi_real {
			let x = -10 + e * 0.1;
			return  TMath::Sqrt(2) * x*  TMath::Power((1 / TMath::Pi()), 1.0 / 4.0) * TMath::Exp(-(x * x / 2));
		},
		[](let& e) -> psi_img { return 0;  },
			[](let& e) -> x_t { return  -10 + e * 0.1;  }
		));
}


std::optional<double> find_element(const std::map<int, std::map<int, double>>& ret_map, int order, int degree) {
	auto search = ret_map.find(order);
	if (search == ret_map.end()) {
		return {};
	}
	
	auto search2 = search->second.find(degree);
	if (search2 == search->second.end()) {
		return {};
	}

	return { search2->second };
}

double hermite_polinome(int order, int degree) {


	if (order < 1) return 0;
	if (degree < 0) return 0;
	if (order == 1){
		return TMath::Power(2.0, degree);
	}
	static std::map<int, std::map<int, double>> ret_buff;
	let ele = find_element(ret_buff, order, degree);
	if (ele) {
		return *ele;
	}
	let h =  hermite_polinome(order, degree - 1) * 2.0 - hermite_polinome(order - 1.0, degree - 1.0) * (degree - (order * 2 - 3));

	ret_buff[order][degree] = h;
	return h;

}


auto hermite(int degree) {

	return [degree](auto x) {
		double ret = 0;
		for (int i = 0; i < degree*2+10; i++) {
			if (degree - i * 2 + 2 < 0) {
				continue;
			}
			//std::cout << x << ", " << i << ", "<<  hermite_polinome(i, degree) << ", "<< degree - i * 2 + 2<<", "<< TMath::Power(x, degree - i * 2 + 2) << std::endl;
			ret += hermite_polinome(i, degree)* TMath::Power(x, degree - i * 2 + 2);

		}
		return ret;
	};
}

auto get_psi(double degree) {
	let N0 = TMath::Sqrt( 1 / (TMath::Power(2, degree) * TMath::Factorial(degree) * TMath::Sqrt( TMath::Pi())));
	//auto hermite1 = hermite(degree);
	
	return[N0, hermite1 = hermite(degree)](const auto& x_range) {
		return wave_function(fill_group_vector(x_range,
			[&](let& e) -> psi_real {
				let x = x_t(e);
				return N0 * hermite1(x) * TMath::Exp(-(x * x / 2));
			},
			[](let& e) -> psi_img { return 0;  },
				[](let& e) -> x_t { return  x_t(e);  }
			));
	};
}

auto get_psi1(double degree) {
	let N0 = TMath::Sqrt(1 / (TMath::Power(2, degree) * TMath::Factorial(degree) * TMath::Sqrt(TMath::Pi())));

	return[N0, hermite1 = hermite(degree)](const auto& e) {
		let x = x_t(e);
		return wave_function_e(
			N0 * hermite1(x) * TMath::Exp(-(x * x / 2)), 
			0, 
			x);
	};
	
}



auto x_range1(double start_, double stop_, double step = -1) {

	size_t Nsteps = 100;
	if (step > 0) {
		Nsteps = (stop_ - start_) / step;
	}
	step = (stop_ - start_) / Nsteps;

	return fill_group_vector(Nsteps,
		[&](let& index) -> psi_real {
			return psi_real(0);
		},
		[&](let& index) -> psi_img {
			return psi_img(0);
		},
		[&](let& index) -> x_t {
			return x_t(start_ + index * step);
		});
}


auto get_normdist(double X_offset, double sigma) {
	double degree=0;
	return[sigma, X_offset, hermite1 = hermite(degree)](const auto& x_range) {
		let ret =  wave_function(fill_group_vector(x_range,
			[&](let& e) -> psi_real {
				let x = x_t(e) - X_offset;
				return  TMath::Exp(-(x * x / (2*sigma*sigma) ));
			},
			[](let& e) -> psi_img { return 0;  },
				[](let& e) -> x_t { return  x_t(e);  }
			));
		let Norm = !ret | ret;
		let ret1 = complex_nr({ 1.0 / TMath::Sqrt( psi_real(Norm)), 0 }) * ret;
		return ret1;
	};
}

template<typename T>
auto time_evolution(double Time, const T& weigths) {
	let x_r = x_range(-10, 10, 0.1);
	wave_function ret(
		fill_group_vector(x_r,
			[&](let& e) -> psi_real { return  0; },
			[&](let& e) -> psi_img { return  0; },
			[&](let& e) -> x_t { return  x_t(e);      }
		)
	);

	for (let& e : weigths) {
		ret = ret + complex_rotate((Energy(e) + 0.5) * Time) * complex_nr({ psi_real(e),psi_img(e) }) * get_psi(Energy(e))(x_r);
	}

	return ret;
}

template <typename T>
auto spectral_decomposition(const T& basis_function) {
	
	return [basis_function](const auto& InputDistribution) {
		group_vector<Energy, psi_real, psi_img>  weigths;

		for (int i = 0; i < 20; i++) {
			let psi0 = get_psi(i);
			weigths.push_back(std::tuple_cat(std::make_tuple(Energy(i)), !psi0(InputDistribution.get_x_range()) | InputDistribution));
		}

		return weigths;
	};
}


int main(int argc, char const* argv[])
{
	
	
	auto offset = get_normdist(-2,1);
	let x_r = x_range(-10, 10, 0.1);

	
	auto weigths = spectral_decomposition(get_psi)(offset(x_r));
	
	for (let& e : weigths) {
		std::cout << e << std::endl;
	}
	auto t0 = time_evolution(0, weigths);
	std::cout <<( !t0 | t0) << std::endl;



	auto ret = time_evolution(10, weigths);
	double N = 2;
	let psi0 = get_psi(N);

	
	let nr = complex_t(1, 5);
	
	std::cout << (!get_psi(1)(x_r) | get_psi(2)(x_r)) <<std::endl;
		
	let V = wave_function( fill_group_vector(x_r,
		[&](let& e) -> psi_real {
			let x = x_t(e);
			return 0.5 * x * x;
		},
		[](let& e) -> psi_img { return 0;  },
		[](let& e) -> x_t { return  x_t(e);  }
	));

	let psi0star = !psi0(x_r) | (0.5*x*x + 0.5* p*p ) * psi0(x_r);
	std::cout << psi0star<< std::endl;
	let psi0starpsi = !psi0(x_r)* psi0(x_r) ;

	double time_index = 0;
	const double frameTime_in_ms = 1000e6;
	clock_t t_last = clock();
	clock_t t_now = clock();
	
	ImGui_plotter<x_t, psi_real> pl1;

	
	
	std::vector<double> x2, y2;
	App desmos(640, 480, "ImDesmos Graphing Calculator",
	[&]{
			t_now = clock();
			auto t_delta = t_now - t_last;
			t_last = t_now;
			time_index += t_delta / frameTime_in_ms;


			ImGui::Begin("ImDesmos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

			ImPlot::SetNextPlotLimitsX(-5, 5);
			ImPlot::SetNextPlotLimitsY(-1, 4);
			if (ImPlot::BeginPlot("##Plot", "x", "y", ImVec2(-1, -1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
				auto limits = ImPlot::GetPlotLimits();
				
				pl1(psi0(x_r) + N + 0.5, "psi");
				pl1(psi0starpsi + N + 0.5, "psi*psi");
			    pl1(V, "V");
				pl1(!offset(x_r)* offset(x_r), "psi");
				let osscilation = time_evolution(time_index * 1e6, weigths);
				


				pl1(!osscilation* osscilation, "osscilation");

				//let x_mean = (!osscilation | x * osscilation);
				//let p_mean = (!osscilation | p * osscilation);

				//x2.push_back(psi_real(x_mean));
				//y2.push_back(psi_real(p_mean));

				//ImPlot::PlotLine("mom", x2.data(), y2.data(), x2.size());

				ImPlot::EndPlot();
			}


			ImGui::SameLine();

			ImGui::End();
	});
	desmos.run();
	return 0;
}

