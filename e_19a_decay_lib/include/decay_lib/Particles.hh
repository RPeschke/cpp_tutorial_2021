#include "platform/platform.hh"


#include <iostream>

#include <random>

#include "TMath.h"


template <typename T>
static inline T remap(T x, T x0, T x1, T y0, T y1) { return y0 + (x - x0) * (y1 - y0) / (x1 - x0); }






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


class DllExport Particle_base {
protected:
	Position_momentum m_position_momentum;
public:
	
	Particle_base(Position_momentum position_momentum);

	void update_intern(df_time time);
	virtual void updata(df_time  time)  =0;
	virtual bool isDecayed() const = 0;
	virtual std::vector<std::shared_ptr<Particle_base>> Decayed_product() const = 0;
	Position_momentum getCoordinates();
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

class DllExport neutrino : public Particle_base {
public:
	mass m_mass = 0;
	static mass get_mass();

	neutrino(Position_momentum position_momentum);


	void updata(df_time time) override;


	bool isDecayed() const override;


	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override;




};





class DllExport muon : public Particle_base {
	const double m_lifeTime = 2.1969811e-6;
	bool isDecayed_ = false;
	double  decay_time;

	double electron_energy() const;

	std::optional<double> calculate_angle_between_electron_and_anti_Neutrino(double E_electron, double P_electron, double E_antiy_neutrino, double P_anti_neut1rino) const;
public:
	static mass get_mass();

	mass m_mass = 105.6583755e6;
	muon(Position_momentum position_momentum);

	void updata(df_time time) override;

	bool isDecayed() const override;

	

	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override;

};

class DllExport pion : public Particle_base {
	const double m_lifeTime = 2.6033e-8;
	bool isDecayed_ = false;
	double  decay_time;
public:
	mass m_mass = 139.57039e6;
	static mass get_mass();

	pion(Position_momentum position_momentum);
	void updata(df_time time) override;
	bool isDecayed() const override;
	std::vector<std::shared_ptr<Particle_base>> Decayed_product() const override;

};

DllExport std::shared_ptr<Particle_base> make_muon(Event_nr Eventnr, px_t px, py_t py, pz_t pz);

DllExport std::shared_ptr<Particle_base> make_pion(Event_nr Eventnr, px_t px, py_t py, pz_t pz);


