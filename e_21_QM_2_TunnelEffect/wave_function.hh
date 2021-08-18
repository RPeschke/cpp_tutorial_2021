#pragma  once





#include "group_helper.hh"
#include "group_plot.hh"
#include "group_io.hh"
#include "group_joins.hh"


#include "group_optional_range.hh"

#include <optional>

#define let  const auto
using namespace group_helper;
	
AXIS_NAME(psi_real, double);
AXIS_NAME(psi_img, double);
AXIS_NAME(x_t, double);

using complex_t = std::tuple<psi_real, psi_img>;
using wave_function_e = std::tuple<psi_real, psi_img, x_t>;


template <typename T1 , typename T2>
auto complex_multiplication(const T1& t1, const T2& t2) {

	return complex_t(
		psi_real(t1) * psi_real(t2) - psi_img(t1) * psi_img(t2),
		psi_img(t1) * psi_real(t2) + psi_real(t1) * psi_img(t2)
	);
}


auto x_range(double start_, double stop_, double step = -1) {

	size_t Nsteps = 100;
	if (step > 0) {
		Nsteps = (stop_ - start_) / step;
	}

	return fill_group_vector(Nsteps,
		[&](let& index) {
			return x_t(start_ + index * step);
		});
}

class wave_function {
public:
	group_vector<psi_real, psi_img, x_t> m_data;
	
	std::function<wave_function(const wave_function&)> m_fun = [](const wave_function& e) {return  wave_function(e); };


	wave_function(const group_vector<psi_real, psi_img, x_t>& data) : m_data(data) {

	}
	auto begin() const {
		return m_data.begin();
	}
	auto end() const {
		return m_data.end();
	}
	complex_t operator|(const wave_function& e)  const{
		if (e.m_data.size() != m_data.size()) {
			throw std::logic_error("size do not match");
		}
		let wave = m_fun(e);
		double ret_real = 0;
		double ret_img = 0;
		let delta_x = x_t(m_data[1]) - x_t(m_data[0]);
		for (int i = 0; i < m_data.size(); ++i) {
			ret_real += psi_real( complex_multiplication( wave.m_data[i] , m_data[i]))* delta_x;
			ret_img  += psi_img(complex_multiplication(wave.m_data[i], m_data[i])) * delta_x;
		}

		return complex_t(ret_real , ret_img);
	}

	wave_function operator*(const wave_function& e)  const {
		if (e.m_data.size() != m_data.size()) {
			throw std::logic_error("size do not match");
		}

		let wave = m_fun(e);
		let delta_x = x_t(m_data[1]) - x_t(m_data[0]);
		auto ret = fill_group_vector(m_data.size(),
			[&](let& index) -> psi_real { return  psi_real(complex_multiplication(m_data[index], wave.m_data[index])); },
			[&](let& index) -> psi_img  { return  psi_img (complex_multiplication(m_data[index], wave.m_data[index])); },
			[&](let& index) -> x_t      { return  x_t(m_data[index]);      }
		);

		return { ret };

	}


	wave_function operator+(const wave_function& e)  const {
		if (e.m_data.size() != m_data.size()) {
			throw std::logic_error("size do not match");
		}

		let wave = m_fun(e);
		let delta_x = x_t(m_data[1]) - x_t(m_data[0]);
		auto ret = fill_group_vector(m_data.size(),
			[&](let& index) -> psi_real { return psi_real(m_data[index]) +  psi_real(wave.m_data[index]); },
			[&](let& index) -> psi_img  { return psi_img(m_data[index])  +  psi_img(wave.m_data[index]);  },
			[&](let& index) -> x_t      { return x_t(m_data[index]); }
		);

		return { ret };

	}

	wave_function operator+(const double e)  const {



		
		auto ret = fill_group_vector(m_data.size(),
			[&](let& index) -> psi_real { return psi_real(m_data[index]) + e; },
			[&](let& index) -> psi_img { return psi_img(m_data[index]) ;  },
			[&](let& index) -> x_t { return x_t(m_data[index]); }
		);

		return { ret };

	}

	wave_function operator-(const double e)  const {
		auto ret = fill_group_vector(m_data.size(),
			[&](let& index) -> psi_real { return psi_real(m_data[index]) - e; },
			[&](let& index) -> psi_img { return psi_img(m_data[index]);  },
			[&](let& index) -> x_t { return x_t(m_data[index]); }
		);

		return { ret };

	}

	wave_function operator-(const wave_function& e)  const {
		if (e.m_data.size() != m_data.size()) {
			throw std::logic_error("size do not match");
		}

		let wave = m_fun(e);
		let delta_x = x_t(m_data[1]) - x_t(m_data[0]);
		auto ret = fill_group_vector(m_data.size(),
			[&](let& index) -> psi_real { return psi_real(m_data[index]) - psi_real(wave.m_data[index]); },
			[&](let& index) -> psi_img { return psi_img(m_data[index]) - psi_img(wave.m_data[index]);  },
			[&](let& index) -> x_t { return x_t(m_data[index]); }
		);

		return { ret };

	}

	wave_function operator!() const {
		auto ret = fill_group_vector(m_data,
			[](let& e) -> psi_real { return  psi_real(e); },
			[](let& e) -> psi_img  { return -psi_img(e);  },
			[](let& e) -> x_t      { return  x_t(e);      }
		);

		return { ret };
	}

	auto get_x_range() const {
		return fill_group_vector(m_data,
			[&](let& index) {
				return x_t(index);
			});
	}
};
