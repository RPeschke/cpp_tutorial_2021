#pragma  once
#include "group_helper.hh"

namespace group_helper {
	class never_itterator {

	};

	template <typename data_T, typename NEXT_FUN_T>
	class fun_optional_itterator {
	public:

		std::remove_reference_t<NEXT_FUN_T> m_fun;

		data_T m_buffer;

		fun_optional_itterator(NEXT_FUN_T&& fun) :m_fun(std::forward< NEXT_FUN_T >(fun)) {
			m_buffer = m_fun();
		}
		auto operator*() const {
			return  *m_buffer;
		}



		fun_optional_itterator& operator++() { m_buffer = m_fun(); return *this; }
		fun_optional_itterator operator++(int) { fun_optional_itterator tmp = *this; ++(*this); return tmp; }

		template <typename T>
		bool operator!= (T&& t) {
			return  bool(m_buffer);
		}

	};

	template <typename  NEXT_FUN_T>
	auto make_fun_optional_itterator(NEXT_FUN_T&& fun) {
		fun_optional_itterator<decltype(fun()), NEXT_FUN_T> ret(
			std::forward<NEXT_FUN_T>(fun)

		);

		return ret;
	}


	template <typename  NEXT_FUN_T>
	auto make_range_optional(NEXT_FUN_T&& fun) {
		return __range__(
			make_fun_optional_itterator(std::forward< NEXT_FUN_T>(fun)),
			never_itterator()
		);
	}
}