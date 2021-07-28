
#include "App.h"

#include <iostream>

#include <random>
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
AXIS_NAME(df_time, double);
AXIS_NAME(x_t, double);
AXIS_NAME(y_t, double);
AXIS_NAME(z_t, double);
AXIS_NAME(Energy_t, double);
AXIS_NAME(px_t, double);
AXIS_NAME(py_t, double);
AXIS_NAME(pz_t, double);

AXIS_NAME(v0_t, double);
AXIS_NAME(vx_t, double);
AXIS_NAME(vy_t, double);
AXIS_NAME(vz_t, double);

AXIS_NAME(mass, double);//ev
AXIS_NAME(v_square, double);

AXIS_NAME(Object_ID, int);
AXIS_NAME(Parent_ID, int);
AXIS_NAME(Event_nr, int);



AXIS_NAME(x_boost_t, double);
AXIS_NAME(y_boost_t, double);
AXIS_NAME(time_boost_t, double);



template <typename... T>
using data_frame = std::vector<std::tuple<T...>>;

using df_objects_old = data_frame<Object_ID, df_time, x_t, y_t>;

using df_objects = group_vector<Event_nr, Parent_ID, Object_ID, df_time, x_t, y_t, z_t, Energy_t, px_t, py_t, pz_t>;

using Position_momentum = std::tuple<Event_nr, Parent_ID, Object_ID, df_time, x_t, y_t, z_t, Energy_t, px_t, py_t, pz_t>;

using four_momentum = std::tuple<Energy_t, px_t, py_t, pz_t>;
using four_position = std::tuple< df_time,  x_t,  y_t, z_t>;


template <typename T>
struct multiplicative_operator {
	std::remove_cvref_t<T> m_op;
	multiplicative_operator(T&& t) :m_op(std::forward<T>(t)) {}

	template <typename T1>
	auto operator()(const T1& t1) {
		return m_op(t1);
	}

	template <typename T1>
	auto operator*(const T1& t1) {
		return m_op(t1);
	}
	template <typename T1>
	auto operator*(multiplicative_operator<T1>& t1) {
		return mmultiplicative_operator([&](const auto& e) {
			return m_op(t1(e));
		});
	}
};

template <typename T1>
auto gammer(const T1& t1) {
	return 1.0 / TMath::Sqrt(1 - (vx_t(t1) * vx_t(t1) +
						        vy_t(t1) * vy_t(t1) +
		                        vz_t(t1) * vz_t(t1)
		                        )
	                       );
}

template <typename T1, typename T2>
auto scaler_product_3(const T1& t1, const T2& t2) {
	return
		std::get<1>(t1) * std::get<1>(t2)
		+ std::get<2>(t1) * std::get<2>(t2)
		+ std::get<3>(t1) * std::get<3>(t2);
}

template <typename T1, typename T2>
auto scaler_product_4(const T1& t1, const T2& t2) {
	return  std::get<0>(t1) * std::get<0>(t2) - scaler_product_3(t1, t2);
}

template <typename T>
auto lorenz_boost(const T& velocity) {
	
	return [velocity, 
			v2 = scaler_product_3(velocity, velocity)
			](const auto& e) {
		const auto r_times_v = scaler_product_3(e, velocity);
		return std::make_tuple(
			std::tuple_element_t<0, std::remove_cvref_t< decltype(e) >>( (std::get<0>(e) * std::get<0>(velocity) - (r_times_v))),
			std::tuple_element_t<1, std::remove_cvref_t< decltype(e) >>( std::get<1>(e) + (std::get<0>(velocity) - 1) * (r_times_v / v2) * std::get<1>(velocity)  - std::get<0>(e) * std::get<1>(velocity)),
			std::tuple_element_t<2, std::remove_cvref_t< decltype(e) >>( std::get<2>(e) + (std::get<0>(velocity) - 1) * (r_times_v / v2) * std::get<2>(velocity)  - std::get<0>(e) * std::get<2>(velocity)),
			std::tuple_element_t<3, std::remove_cvref_t< decltype(e) >>( std::get<3>(e) + (std::get<0>(velocity) - 1) * (r_times_v / v2) * std::get<3>(velocity)  - std::get<0>(e) * std::get<3>(velocity))
		);
	};
}


template <typename T>
auto lorenz_boost_invert(const T& velocity) {
	let velocity_invert = std::make_tuple(
		v0_t(velocity),
		vx_t(-vx_t(velocity)),
		vy_t(-vy_t(velocity)),
		vz_t(-vz_t(velocity))
	);
	return lorenz_boost(velocity_invert);
}



template <typename T>
auto rotate_z(const T& rot_angle) {

	return [rot_angle](const auto& e) {
		
		return std::make_tuple(
			std::tuple_element_t<0, std::remove_cvref_t< decltype(e) >>(std::get<0>(e) ),
			std::tuple_element_t<1, std::remove_cvref_t< decltype(e) >>(std::get<1>(e)* TMath::Cos(rot_angle) - std::get<2>(e) * TMath::Sin(rot_angle)),
			std::tuple_element_t<2, std::remove_cvref_t< decltype(e) >>(std::get<1>(e)* TMath::Sin(rot_angle) + std::get<2>(e) * TMath::Cos(rot_angle)),
			std::tuple_element_t<3, std::remove_cvref_t< decltype(e) >>(std::get<3>(e))
		);
	};
}

template <typename... T> 
auto get_elements() {
	return [&](const auto& e) {
		std::make_tuple(
			T(e)...
		);
	};
}

auto get_four_position() {
	return get_elements<df_time, x_t,y_t,z_t>();
}

Object_ID get_new_Object_ID() {
	static Object_ID id;
	id = id + 1;
	return id;
}

double get_random() {
	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	static std::uniform_real_distribution<> dis(0.0, 1.0);
	return dis(gen);
}
double get_random_exponential(double lambda__) {
	static	std::random_device rd;
	static  std::mt19937 gen(rd());
	std::exponential_distribution<> d(lambda__);
	return d(gen);
}



template <typename... T>
v_square get_Velocity_square(const std::tuple<T...>& t) {

	return (px_t(t) * px_t(t) + py_t(t) * py_t(t) + pz_t(t) * pz_t(t))
		/ // ---------------------------------------------------------------------------------------
		(Energy_t(t) * Energy_t(t));
}

template <typename T>
auto get_Velocity_from_Momentum(const T& t) {
	auto f_momentum = std::make_tuple(Energy_t(t), px_t(t), py_t(t), pz_t(t));
	const auto m0 = TMath::Sqrt( scaler_product_4(f_momentum,f_momentum));
	return std::make_tuple(
		v0_t(Energy_t(t) / m0),
		vx_t(px_t(t) / m0),
		vy_t(py_t(t) / m0),
		vz_t(pz_t(t) / m0)
	);
}


class Particle_base {
protected:
	Position_momentum m_position_momentum;
public:
	
	Particle_base(Position_momentum position_momentum) : m_position_momentum(std::move(position_momentum)) {
		std::cout << m_position_momentum << std::endl;
	}

	void update_intern(df_time time) {
		auto deltaTime = time- df_time(m_position_momentum) ;
		auto x = x_t(m_position_momentum) + px_t(m_position_momentum) / Energy_t(m_position_momentum) * deltaTime;
		auto y = y_t(m_position_momentum) + py_t(m_position_momentum) / Energy_t(m_position_momentum) * deltaTime;
		auto z = z_t(m_position_momentum) + pz_t(m_position_momentum) / Energy_t(m_position_momentum) * deltaTime;

		m_position_momentum = std::make_tuple(
			Event_nr(m_position_momentum),
			Parent_ID(m_position_momentum),
			Object_ID(m_position_momentum),
			time, x, y, z,
			Energy_t(m_position_momentum), px_t(m_position_momentum), py_t(m_position_momentum), pz_t(m_position_momentum)
		);
	}
	virtual void updata(df_time  time)  =0;
	virtual bool isDecayed() const = 0;
	virtual std::vector<std::shared_ptr<Particle_base>> Decayed_product() const = 0;
	Position_momentum getCoordinates() {
		return m_position_momentum;
	}
	virtual ~Particle_base() {}
};

class electron : public Particle_base {
public:
	mass m_mass = 511e3; 
	static mass get_mass() {
		return 511e3;
	}
	electron(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {

	}


	void updata( df_time time) override{
		update_intern(time);

	}


	bool isDecayed() const override
	{
		return false;
	}


	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}




};

class neutrino : public Particle_base {
public:
	mass m_mass = 511e3;
	static mass get_mass() {
		return 0;
	}
	neutrino(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {

	}


	void updata(df_time time) override {
		update_intern(time);

	}


	bool isDecayed() const override
	{
		return false;
	}


	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}




};





class muon : public Particle_base {
	const double m_lifeTime = 2.1969811e-6;
	bool isDecayed_ = false;
	double  decay_time;

	double electron_energy() const {
		bool parameter_found = false;
		const double Gf = 1.17e-23;
		double e_rand = 0;
		while(true) {
			e_rand = get_random()*m_mass/2;
			double w_rand = get_random()*1.2e-17;
			double w = 2 / TMath::Power(2 * TMath::Pi(),3)  * Gf * Gf * m_mass * m_mass * e_rand * e_rand * (1 - 4 * e_rand / (3 * m_mass));
			parameter_found = w > w_rand;
			if (parameter_found) {
				break;
			}
			//std::cout << e_rand << ", " << w_rand << ", " << w << ", " << parameter_found << std::endl;
		} 
		
		return e_rand;
		
	}
public:
	static mass get_mass() {
		return 105.6583755e6;
	}
	mass m_mass = 105.6583755e6;
	muon(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {
		decay_time = df_time(position_momentum) +  get_random_exponential(1.0 / m_lifeTime);
	}

	void updata(df_time time) override
	{
		if (isDecayed_) {
			return;
		}
		const auto old_time = df_time(m_position_momentum);
		update_intern(time);


		auto v2 = get_Velocity_square(m_position_momentum);
		auto gamma = 1 / TMath::Sqrt(1 - v2);
		auto time_local = time / gamma;

		isDecayed_ = decay_time < time_local;


	}


	bool isDecayed() const override
	{
		return isDecayed_;
	}
	
	std::optional<double> calculate_angle_between_electron_and_anti_Neutrino(double E_electron, double P_electron, double E_antiy_neutrino , double P_anti_neut1rino) const{
		
		double p_neutrino_square_old = 0;
		for (double i =0 ; i< TMath::Pi(); i+= 0.001){
			let e_neutrino = m_mass - E_electron - E_antiy_neutrino;
			let px_neutrino = -P_anti_neut1rino * TMath::Sin(i);
			let pz_neutrino = -P_electron  -P_anti_neut1rino * TMath::Cos(i);
			let p_neutrino_square = e_neutrino * e_neutrino - px_neutrino * px_neutrino - pz_neutrino * pz_neutrino;
			//std::cout << i << ", " << p_neutrino_square << std::endl;
			if (p_neutrino_square_old *p_neutrino_square  < 0){
				return i;
			}
			p_neutrino_square_old = p_neutrino_square;
		}

		return {};
	}

	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override {
	
		bool done = false;
		const auto m_electron = electron::get_mass();
		const auto m_neutrino = 0.0;
		auto E_electron = electron_energy();
		auto P_electron = TMath::Sqrt(E_electron * E_electron - m_electron * m_electron);

		auto E_antiy_neutrino = electron_energy();
		auto P_anti_neut1rino = TMath::Sqrt(E_antiy_neutrino * E_antiy_neutrino - m_neutrino * m_neutrino);
		double theta = 0;
		while(true){
			E_electron = electron_energy();
			P_electron = TMath::Sqrt(E_electron * E_electron - m_electron * m_electron);

			E_antiy_neutrino = electron_energy();
			P_anti_neut1rino = TMath::Sqrt(E_antiy_neutrino * E_antiy_neutrino - m_neutrino * m_neutrino);

			auto theta_optional = calculate_angle_between_electron_and_anti_Neutrino(E_electron, P_electron, E_antiy_neutrino, P_anti_neut1rino);
			if (theta_optional){
				theta = *theta_optional;
				break;
			}
		} 

		auto E_neutrino = m_mass - E_electron - E_antiy_neutrino;
		auto P_neutrino = TMath::Sqrt(E_neutrino * E_neutrino - m_neutrino * m_neutrino);

		const auto phi =;

		auto P4_electron = four_momentum(
			E_electron,
			P_electron,
			0,
			0
		);

		auto rotate_phi = rotate_z(get_random() * 2 * TMath::Pi());
		auto boost_v = lorenz_boost_invert( get_Velocity_from_Momentum(m_position_momentum) );

		auto P4_electron_lab = boost_v(rotate_phi(P4_electron));

		auto electron1 = std::make_shared<electron>(
			std::make_tuple(
				Event_nr(m_position_momentum),
				Parent_ID(Object_ID(m_position_momentum)),
				Object_ID(get_new_Object_ID()),
				df_time(m_position_momentum),

				x_t(m_position_momentum), y_t(m_position_momentum), z_t(m_position_momentum),
				Energy_t(P4_electron_lab), px_t(P4_electron_lab), py_t(P4_electron_lab), pz_t(P4_electron_lab)
			)
			);
		auto P4_anti_neutrino = four_momentum(
			E_antiy_neutrino,
			E_antiy_neutrino * TMath::Cos(theta),
			E_antiy_neutrino * TMath::Sin(theta),
			0
		);

		auto P4_anti_eutrino_lab = boost_v(rotate_phi(P4_anti_neutrino));
		auto anti_neutrino1 = std::make_shared<neutrino>(
			std::make_tuple(
				Event_nr(m_position_momentum),
				Parent_ID(Object_ID(m_position_momentum)),
				Object_ID(get_new_Object_ID()),
				df_time(m_position_momentum),

				x_t(m_position_momentum), y_t(m_position_momentum), z_t(m_position_momentum),
				Energy_t(P4_anti_eutrino_lab), px_t(P4_anti_eutrino_lab), py_t(P4_anti_eutrino_lab), pz_t(P4_anti_eutrino_lab)
			)
			);


		auto P4_neutrino = four_momentum(
			m_mass - E_electron - E_antiy_neutrino,
			- px_t(P4_electron) - px_t(P4_anti_neutrino),
			- py_t(P4_electron) - py_t(P4_anti_neutrino),
			- pz_t(P4_electron) - pz_t(P4_anti_neutrino)
		);


		auto P4_neutrino_lab = boost_v(rotate_phi(P4_neutrino));
		auto neutrino1 = std::make_shared<neutrino>(
			std::make_tuple(
				Event_nr(m_position_momentum),
				Parent_ID(Object_ID(m_position_momentum)),
				Object_ID(get_new_Object_ID()),
				df_time(m_position_momentum),

				x_t(m_position_momentum), y_t(m_position_momentum), z_t(m_position_momentum),
				Energy_t(P4_neutrino_lab), px_t(P4_neutrino_lab), py_t(P4_neutrino_lab), pz_t(P4_neutrino_lab)
			)
			);

		return { electron1, anti_neutrino1, neutrino1 };
	}




};

class pion : public Particle_base {
	const double m_lifeTime = 2.6033e-8;
	bool isDecayed_ = false;
	double  decay_time;
public:
	mass m_mass = 139.57039e6;
	
	static mass get_mass() {
		return 139.57039e6;
	}

	pion(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {
		decay_time = df_time(position_momentum) + get_random_exponential(1.0/m_lifeTime);
		
	}

	void updata(df_time time) override
	{
		if (isDecayed_){
			return;
		}
		const auto old_time = df_time(m_position_momentum);
		update_intern(time);
		
		
		auto v2 = get_Velocity_square(m_position_momentum);
		auto gamma = 1 / TMath::Sqrt(1 - v2);
		auto time_local = time / gamma;
		
		isDecayed_ = decay_time < time_local;


	}


	bool isDecayed() const override
	{
		return isDecayed_;
	}


	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override{
		const auto m_muon = muon::get_mass();
		const auto m_neutrino= 0.0;
		auto E_muon = (m_mass * m_mass + m_muon * m_muon - m_neutrino * m_neutrino) / (2 * m_mass);
		auto P_muon = TMath::Sqrt(E_muon * E_muon - m_muon * m_muon);

		auto E_neutrino = (m_mass * m_mass +  m_neutrino * m_neutrino - m_muon * m_muon) / (2 * m_mass);
		auto P_neutrino = TMath::Sqrt(E_neutrino * E_neutrino - m_neutrino * m_neutrino);

		

		auto P4_muon =  four_momentum(
			Energy_t(E_muon),
			px_t(P_muon),
			py_t(0),
			pz_t(0)
		);
		
		auto rotate_phi = rotate_z(get_random() * 2 * TMath::Pi());
		auto boost_v = lorenz_boost_invert(get_Velocity_from_Momentum(m_position_momentum));
		auto P4_muon_lab = boost_v(rotate_phi(P4_muon));
		auto muon1 = std::make_shared<muon>(
			std::make_tuple(
				Event_nr(m_position_momentum), 
				Parent_ID(Object_ID(m_position_momentum)), 
				Object_ID(get_new_Object_ID()), 
				df_time(m_position_momentum), 

				x_t(m_position_momentum), y_t(m_position_momentum), z_t(m_position_momentum), 
				Energy_t(P4_muon_lab), px_t(P4_muon_lab), py_t(P4_muon_lab), pz_t(P4_muon_lab)
			)
			);
		auto P4_neutrino = four_momentum(
			Energy_t(E_neutrino),
			px_t(-P_neutrino ),
			py_t(0),
			pz_t(0)
		);

		auto P4_neutrino_lab = boost_v(rotate_phi(P4_neutrino));
		auto neutrino1 = std::make_shared<neutrino>(
			std::make_tuple(
				Event_nr(m_position_momentum),
				Parent_ID(Object_ID(m_position_momentum)),
				Object_ID(get_new_Object_ID()),
				df_time(m_position_momentum),

				x_t(m_position_momentum), y_t(m_position_momentum), z_t(m_position_momentum),
				Energy_t(P4_neutrino_lab), px_t(P4_neutrino_lab), py_t(P4_neutrino_lab), pz_t(P4_neutrino_lab)
			)
			);
		return { muon1, neutrino1 };
	}




};

std::shared_ptr<Particle_base> make_muon(Event_nr Eventnr, px_t px, py_t py, pz_t pz) {
	let m_mass = muon::get_mass();
	return std::make_shared< muon>(std::make_tuple(
		Eventnr, Parent_ID(0), Object_ID(get_new_Object_ID()), df_time(0), x_t(0), y_t(0), z_t(0), Energy_t(TMath::Sqrt( m_mass*m_mass + px*px + py* py + pz*pz)) , px_t(px), py_t(py), pz_t(pz)
	));
}

std::shared_ptr<Particle_base> make_pion(Event_nr Eventnr, px_t px, py_t py, pz_t pz) {
	let m_mass = pion::get_mass();
	return std::make_shared< pion>(std::make_tuple(
		Eventnr, Parent_ID(0), Object_ID(get_new_Object_ID()), df_time(0), x_t(0), y_t(0), z_t(0), Energy_t(TMath::Sqrt(m_mass * m_mass + px * px + py * py + pz * pz)), px_t(px), py_t(py), pz_t(pz)
	));
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
