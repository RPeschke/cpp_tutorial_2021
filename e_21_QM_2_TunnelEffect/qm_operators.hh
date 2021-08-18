#pragma  once


#include "wave_function.hh"



class qm_operators {
	std::function<wave_function(const wave_function&)> m_op;
public:

	qm_operators(std::function<wave_function(const wave_function&)> op) :m_op(std::move(op)) {}

	wave_function operator*(const wave_function& psi) const {
		return m_op(psi);
	}

	wave_function apply(const wave_function& psi) const {
		return m_op(psi);
	}

	qm_operators operator*(const qm_operators& op2) const {
		return qm_operators(
			[op1 = *this, op2](const wave_function& e) {
			return  op1.apply(op2.apply(e));
		}
		);
	}


	qm_operators operator+(const qm_operators& op2) const {
		return qm_operators(
			[op1 = *this, op2](const wave_function& e) {
			return  op1.apply(e) + op2.apply(e);
		}
		);
	}
	qm_operators operator-(const qm_operators& op2) const {
		return qm_operators(
			[op1 = *this, op2](const wave_function& e) {
			return  op1.apply(e) - op2.apply(e);
		}
		);
	}







};

qm_operators complex_nr(complex_t nr) {
	return qm_operators(

		[nr](const wave_function& wf) {
			wave_function ret(

				fill_group_vector(wf.m_data,
					[&](let& e) ->psi_real { return psi_real(complex_multiplication(nr, e));  },
					[&](let& e) ->psi_img { return psi_img(complex_multiplication(nr, e));  },
					[](let& e) ->x_t { return x_t(e);  }
				)
			);


			return ret;
		}
	);
}



qm_operators complex_rotate(double rot) {

	complex_t nr = {
		TMath::Cos(rot),
		TMath::Sin(rot)
	};
	return qm_operators(

		[nr](const wave_function& wf) {
			return wave_function(
				fill_group_vector(wf.m_data,
					[&](let& e) ->psi_real { return psi_real(complex_multiplication(nr, e));  },
					[&](let& e) ->psi_img { return psi_img(complex_multiplication(nr, e));  },
					[](let& e) ->x_t { return x_t(e);  }
				)
			);
		}
	);
}



qm_operators operator*(double x, const qm_operators& op) {
	return complex_nr({ x,0 }) * op;
}