
#include "decay_lib/Particles.hh"


auto get_four_position() {
	return get_elements<df_time, x_t, y_t, z_t>();
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


Particle_base::Particle_base(Position_momentum position_momentum) : m_position_momentum(std::move(position_momentum)) {
	std::cout << m_position_momentum << std::endl;
}



void Particle_base::update_intern(df_time time) {
	auto deltaTime = time - df_time(m_position_momentum);
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


Position_momentum Particle_base::getCoordinates() {
	return m_position_momentum;
}




neutrino::neutrino(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {

}


void neutrino::updata(df_time time)  {
	update_intern(time);

}



bool neutrino::isDecayed() const {
	return false;
}


std::vector<std::shared_ptr<Particle_base>> neutrino::Decayed_product() const {
	throw std::logic_error("The method or operation is not implemented.");
}

mass neutrino::get_mass() {
	return 0;
}




double muon::electron_energy() const {
	bool parameter_found = false;
	const double Gf = 1.17e-23;
	double e_rand = 0;
	while (true) {
		e_rand = get_random() * m_mass / 2;
		double w_rand = get_random() * 1.2e-17;
		double w = 2 / TMath::Power(2 * TMath::Pi(), 3) * Gf * Gf * m_mass * m_mass * e_rand * e_rand * (1 - 4 * e_rand / (3 * m_mass));
		parameter_found = w > w_rand;
		if (parameter_found) {
			break;
		}
		//std::cout << e_rand << ", " << w_rand << ", " << w << ", " << parameter_found << std::endl;
	}

	return e_rand;

}


mass  muon::get_mass() {
	return 105.6583755e6;
}


muon::muon(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {
	decay_time = df_time(position_momentum) + get_random_exponential(1.0 / m_lifeTime);
}



void muon::updata(df_time time){
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



bool muon::isDecayed() const {
	return isDecayed_;
}


std::optional<double> muon::calculate_angle_between_electron_and_anti_Neutrino(double E_electron, double P_electron, double E_antiy_neutrino, double P_anti_neut1rino) const {

	double p_neutrino_square_old = 0;
	for (double i = 0; i < TMath::Pi(); i += 0.001) {
		let e_neutrino = m_mass - E_electron - E_antiy_neutrino;
		let px_neutrino = -P_anti_neut1rino * TMath::Sin(i);
		let pz_neutrino = -P_electron - P_anti_neut1rino * TMath::Cos(i);
		let p_neutrino_square = e_neutrino * e_neutrino - px_neutrino * px_neutrino - pz_neutrino * pz_neutrino;
		//std::cout << i << ", " << p_neutrino_square << std::endl;
		if (p_neutrino_square_old * p_neutrino_square < 0) {
			return i;
		}
		p_neutrino_square_old = p_neutrino_square;
	}

	return {};
}


std::vector<std::shared_ptr<Particle_base>> muon::Decayed_product() const  {

	bool done = false;
	const auto m_electron = electron::get_mass();
	const auto m_neutrino = 0.0;
	auto E_electron = electron_energy();
	auto P_electron = TMath::Sqrt(E_electron * E_electron - m_electron * m_electron);

	auto E_antiy_neutrino = electron_energy();
	auto P_anti_neut1rino = TMath::Sqrt(E_antiy_neutrino * E_antiy_neutrino - m_neutrino * m_neutrino);
	double theta = 0;
	while (true) {
		E_electron = electron_energy();
		P_electron = TMath::Sqrt(E_electron * E_electron - m_electron * m_electron);

		E_antiy_neutrino = electron_energy();
		P_anti_neut1rino = TMath::Sqrt(E_antiy_neutrino * E_antiy_neutrino - m_neutrino * m_neutrino);

		auto theta_optional = calculate_angle_between_electron_and_anti_Neutrino(E_electron, P_electron, E_antiy_neutrino, P_anti_neut1rino);
		if (theta_optional) {
			theta = *theta_optional;
			break;
		}
	}

	auto E_neutrino = m_mass - E_electron - E_antiy_neutrino;
	auto P_neutrino = TMath::Sqrt(E_neutrino * E_neutrino - m_neutrino * m_neutrino);



	auto P4_electron = four_momentum(
		E_electron,
		P_electron,
		0,
		0
	);

	auto rotate_phi = rotate_z(get_random() * 2 * TMath::Pi());
	auto boost_v = lorenz_boost_invert(get_Velocity_from_Momentum(m_position_momentum));

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
		-px_t(P4_electron) - px_t(P4_anti_neutrino),
		-py_t(P4_electron) - py_t(P4_anti_neutrino),
		-pz_t(P4_electron) - pz_t(P4_anti_neutrino)
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


mass pion::get_mass() {
	return 139.57039e6;
}



pion::pion(Position_momentum position_momentum) : Particle_base(std::move(position_momentum)) {
	decay_time = df_time(position_momentum) + get_random_exponential(1.0 / m_lifeTime);

}



void pion::updata(df_time time) {
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


bool pion::isDecayed() const {
	return isDecayed_;
}


std::vector<std::shared_ptr<Particle_base>> pion::Decayed_product() const  {
	const auto m_muon = muon::get_mass();
	const auto m_neutrino = 0.0;
	auto E_muon = (m_mass * m_mass + m_muon * m_muon - m_neutrino * m_neutrino) / (2 * m_mass);
	auto P_muon = TMath::Sqrt(E_muon * E_muon - m_muon * m_muon);

	auto E_neutrino = (m_mass * m_mass + m_neutrino * m_neutrino - m_muon * m_muon) / (2 * m_mass);
	auto P_neutrino = TMath::Sqrt(E_neutrino * E_neutrino - m_neutrino * m_neutrino);



	auto P4_muon = four_momentum(
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
		px_t(-P_neutrino),
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



std::shared_ptr<Particle_base> make_muon(Event_nr Eventnr, px_t px, py_t py, pz_t pz) {
	let m_mass = muon::get_mass();
	return std::make_shared< muon>(std::make_tuple(
		Eventnr, Parent_ID(0), Object_ID(get_new_Object_ID()), df_time(0), x_t(0), y_t(0), z_t(0), Energy_t(TMath::Sqrt(m_mass * m_mass + px * px + py * py + pz * pz)), px_t(px), py_t(py), pz_t(pz)
	));
}

std::shared_ptr<Particle_base> make_pion(Event_nr Eventnr, px_t px, py_t py, pz_t pz) {
	let m_mass = pion::get_mass();
	return std::make_shared< pion>(std::make_tuple(
		Eventnr, Parent_ID(0), Object_ID(get_new_Object_ID()), df_time(0), x_t(0), y_t(0), z_t(0), Energy_t(TMath::Sqrt(m_mass * m_mass + px * px + py * py + pz * pz)), px_t(px), py_t(py), pz_t(pz)
	));
}