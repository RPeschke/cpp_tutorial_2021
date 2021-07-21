#include "group_helper.hh"
#include "group_optional_range.hh"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include "TMath.h"
#include <bitset>

#include <optional>

using namespace group_helper;


template <typename Itterator_t>
class group_itt_base {

public:
	using iterator_category = std::input_iterator_tag;


	group_itt_base(Itterator_t ptr) : m_itt(ptr) {}
	group_itt_base() {}
	Itterator_t m_itt;


};
template <typename T1, typename T2>
bool operator== (const group_itt_base<T1>& a, const group_itt_base<T2>& b) { return a.m_itt == b.m_itt; };
template <typename T1, typename T2>
bool operator!= (const group_itt_base<T1>& a, const group_itt_base<T2>& b) { return a.m_itt != b.m_itt; };

//template <typename T1>
//bool operator== (const group_itt_base<T1>& a, const never_itterator& b) { return false; };
//template <typename T1>
//bool operator!= (const group_itt_base<T1>& a, const never_itterator& b) { return true; };
//
//template <typename T1>
//bool operator== (const never_itterator& b, const group_itt_base<T1>& a) { return false; };
//template <typename T1>
//bool operator!= (const never_itterator& b, const group_itt_base<T1>& a) { return true; };


template <typename T1, typename T2>
bool operator== (const group_itt_base<T1>& a, T2&&) { return false; };
template <typename T1, typename T2>
bool operator!= (const group_itt_base<T1>& a, T2&& b) { return true; };

template <typename Itterator_t, typename Fun_T>
class group_itt : public group_itt_base<Itterator_t> {
public:

	std::remove_reference_t<Fun_T> m_fun;

	group_itt(Itterator_t itt, Fun_T&& fun) : group_itt_base<Itterator_t>(itt), m_fun(std::forward< Fun_T >(fun)) {}
	auto operator*() const {
		return  this->m_itt;
	}

	auto operator*() {
		return  this->m_itt;
	}


	group_itt& operator++() { this->m_itt = m_fun(); return *this; }
	group_itt operator++(int) { group_itt tmp = *this; ++(*this); return tmp; }

	template <typename T>
	bool operator!= (T&& t) {
		return this->m_itt != t.m_itt;
	}

};


template <typename VALUE_T, typename Fun_T>
class group_itt_fun : public group_itt_base<VALUE_T> {
public:
	std::remove_reference_t<Fun_T> m_fun;

	group_itt_fun(VALUE_T itt, Fun_T&& fun) : group_itt_base<VALUE_T>(itt), m_fun(std::forward< Fun_T >(fun)) {}
	auto operator*() const {
		return  m_fun();
	}

	auto operator*() {
		return  m_fun(*this->m_itt);
	}
	auto* operator->() { return &(m_fun(*this->m_itt)); }

	group_itt_fun& operator++() { ++(this->m_itt); return *this; }
	group_itt_fun operator++(int) { group_itt_fun tmp = *this; ++(*this); return tmp; }

	template <typename T>
	bool operator!= (T&& t) {
		return this->m_itt != t.m_itt;
	}
};

template <typename Fun_T, typename itterator_t>
auto make_grout_itt(Fun_T&& fun, itterator_t itt) {

	return group_itt_fun<itterator_t, Fun_T>(itt, std::forward<Fun_T>(fun));
}

template <typename T1, typename T>
auto get(const std::vector<T>& vec) {

	return __range__(
		make_grout_itt([](const auto& x) {  return T1(x).m_value; }, vec.begin()),
		group_itt_base<decltype(vec.end())>(vec.end())
	);
}

template <typename T>
class Numbers_itt :public group_itt_base<T> {
public:
	T m_end;
	Numbers_itt(T Start_, T End_) :group_itt_base<T>(Start_), m_end(End_) {}
	auto operator*() const {
		return  this->m_itt;
	}

	auto operator*() {
		return  this->m_itt;
	}
	

	Numbers_itt& operator++() { ++(this->m_itt); return *this; }
	Numbers_itt operator++(int) { Numbers_itt tmp = *this; ++(*this); return tmp; }

	template <typename T>
	bool operator!= (T&& t) {
		return this->m_itt != m_end;
	}
};


template <typename T>
auto Numbers(T start_, T end_) {
	return 	__range__(
		Numbers_itt(start_,end_),
		never_itterator()
	);
}

template <typename Fun_T, typename T>
auto transform_range(Fun_T&& fun, const T& range_) {


	return __range__(
		make_grout_itt(std::forward<Fun_T>(fun), range_.begin()),
		group_itt_base<decltype(range_.end())>(range_.end())
	);
}
namespace group_ns {

	template <typename T>
	auto sin(T&& t) {
		return transform_range(
			[](const auto& x) {
			return  TMath::Sin(x);
		},
			std::forward<T>(t)
			);

	}
}
template <typename Fun_T, typename itterator_t>
auto make_grout_itt_fun(Fun_T&& fun, itterator_t itt) {
	auto val = fun();
	return group_itt<decltype(val), Fun_T>(val, std::forward<Fun_T>(fun));
}

template <typename T>
auto repeat(const T& val) {
	return __range__(
		make_grout_itt_fun([val]() {return val; }, 0),
		never_itterator()
	);
}

template <typename data_T , typename NEXT_FUN_T, typename VALID_FUNT_T>
class fun2_itterator {
public:

	std::remove_reference_t<NEXT_FUN_T> m_fun;
	std::remove_reference_t<VALID_FUNT_T> m_fun_valid;
	data_T m_buffer;

	fun2_itterator( NEXT_FUN_T&& fun, VALID_FUNT_T&& valid_fun) :m_fun_valid(std::forward< VALID_FUNT_T >(valid_fun)), m_fun(std::forward< NEXT_FUN_T >(fun)) {}
	auto operator*() const {
		return  m_buffer;
	}

	auto operator*() {
		return  m_buffer;
	}


	fun2_itterator& operator++() { m_buffer = m_fun(); return *this; }
	fun2_itterator operator++(int) { fun2_itterator tmp = *this; ++(*this); return tmp; }

	template <typename T>
	bool operator!= (T&& t) {
		return  m_fun_valid();
	}

};

template <typename  NEXT_FUN_T, typename VALID_FUNT_T>
auto make_fun2itterator(NEXT_FUN_T&& fun, VALID_FUNT_T&& valid_fun) {
	fun2_itterator<int, NEXT_FUN_T, VALID_FUNT_T> ret(
		std::forward<NEXT_FUN_T>(fun),
		std::forward<VALID_FUNT_T>(valid_fun)
		);

	return ret;
}

//template <T>
//class zip_itt {
//public:
//	T m_tuple_itt;
//	T m_tuple_itt_end;
//	zip_itt(T Start_tuple_itt, T End_) : m_tuple_itt(std::move(Start_tuple_itt)), m_tuple_itt_end(std::move(End_)) {}
//	auto operator*() const {
//		return  std::make_tuple(*std::get<0>(m_tuple_itt), *std::get<1>(m_tuple_itt));
//	}
//
//	
//
//	zip_itt& operator++() { ++( std::get<0>(m_tuple_itt)), ++(std::get<1>(m_tuple_itt)); return *this; }
//	zip_itt operator++(int) { zip_itt tmp = *this; ++(*this); return tmp; }
//
//	template <typename T1>
//	bool operator!= (T1&& t) {
//		return std::get<0>(m_tuple_itt)!= std::get<0>(t.m_tuple_itt)  && (std::get<1>(m_tuple_itt)) != std::get<1>(t.m_tuple_itt);
//	}
//};
//




struct Compare_true {
	template<typename T1, typename T2>
	constexpr bool operator()(T1&&, T2&&) const noexcept
	{
		return true;
	}

};

struct to_pair
{
	template<typename T1, typename T2>
	constexpr auto operator()(T1&& t1, T2&& t2) const noexcept
	{
		return std::make_pair(t1, t2);
	}
};

template <typename T1, typename T2, typename Comparision_T = Compare_true, typename projecttion_t = to_pair>
auto vec_join(const T1& t1, const T2& t2, Comparision_T comp = Compare_true(), projecttion_t project = to_pair()) {

	std::vector<  decltype(project(t1[0], t2[0]))  > ret;


	for (const auto& e1 : t1) {
		for (const auto& e2 : t2) {
			if (comp(e1, e2)) {
				ret.push_back(project(e1, e2));
			}
		}
	}
	return ret;
}


template <typename T1, typename T2, typename Comparision_T = Compare_true, typename projecttion_t = to_pair>
auto vec_zip(const T1& t1,const  T2& t2, projecttion_t project = to_pair()) {

	std::vector<  decltype(project(*t1.begin(), *t2.begin()))  > ret;

	auto t1_itt = t1.begin();
	auto t2_itt = t2.begin();
	while (t1_itt != t1.end() && t2_itt != t2.end()){
		ret.push_back(project(*t1_itt, *t2_itt));
		++t1_itt;
		++t2_itt;
	}
	return ret;

}



template <typename T1, typename T2, typename projecttion_t = to_pair>
auto l_zip(const T1& t1, const  T2& t2, projecttion_t project = to_pair()) {


	return make_range_optional([
		t1_itt = t1.begin(),
		t1_end = t1.end(),
		t2_itt = t2.begin(),
		t2_end = t2.end(),
		project
	]() mutable->std::optional< decltype(project(*t1.begin(), *t2.begin()))  >{
		if (!(t1_itt != t1_end && t2_itt != t2_end))  return {};

		auto ret = project(*t1_itt, *t2_itt);
		++t1_itt; ++t2_itt;
		
		return ret;

	});



}

template <typename T>
auto to_vector(T&& t) {
	std::vector<decltype(*t.begin())> ret;
	for (const auto e : t) {
		ret.push_back(e);
	}
	return ret;
}

template <typename T>
const std::vector<T>& to_vector(const std::vector<T>& t) {
	return t;
}

template <typename T1, typename T2, typename projecttion_t = to_pair>
auto l_join(const T1& t1, const T2& t2, projecttion_t project = to_pair()) {


	return make_range_optional([
			t1_itt = t1.begin(),
			t2_index = 0,
			t1,
			t2 = to_vector(t2),
			project
	]() mutable->std::optional< decltype(project(*t1.begin(), *t2.begin()))  >{
			if (t2_index == t2.size()) {
				t2_index =0;
				++t1_itt;
			}
			
			if (!(t1_itt != t1.end()))  return {};
			auto ret = project(*t1_itt, t2[t2_index]);
			++t2_index;

			return ret;
			

		});

}



template <typename T>
auto l_numbers(T&& t) {
	return make_range_optional([I = 0, t]() mutable->std::optional< std::remove_reference_t<T>>{
		if (I >= t)  return {};
		int inter = I;
		++I;
		return { inter };
	});
}

template <typename T1, typename T2>
auto l_numbers(T1&& start_, T2&& end_) {
	return make_range_optional([I = start_, end_]() mutable->std::optional<std::remove_reference_t<T1>>{
		if (I >= end_)  return {};
		int inter = I;
		++I;
		return { inter };
	});
}


int main(int argc, char** argv) {


 	for (auto e : l_join(l_numbers(0, 5), l_numbers(5, 10), {})) {
 		std::cout << e.first << "  " << e.second << "\n";
 	}

	auto asdasdaweqe =  to_vector(l_numbers(5, 10));
	for (auto e : l_join(l_numbers(0, 5), asdasdaweqe, {})) {
		std::cout << e.first << "  " << e.second << "\n";
	}

	for (auto e : l_zip(l_numbers(0, 5), l_numbers(5,10), {})) {
		std::cout << e.first << "  " << e.second << "\n";
	}
	auto opf = [](auto i) -> std::optional<double> {
		if (i > 10) {
			return i++;
		}
		return {};
	};
	decltype(opf(1)) a;

	auto it = make_fun_optional_itterator([i = 10]() mutable->std::optional<int>  {
		return i++;
	});

	std::cout << *it << std::endl;
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;





	std::cout << *opf(11) << std::endl;
	std::cout << *opf(1) << std::endl;
	std::cout << bool(opf(1)) << std::endl;
	std::cout << bool(opf(11)) << std::endl;
	auto itt1 = make_fun2itterator([i = int(0)]()mutable  { return ++i; }, [] { return true; });
	auto num1 = __range__(
		itt1,
		never_itterator()
	);

	for (auto e : num1) {
		std::cout << e << std::endl;
	}
	auto x = Numbers(0, 10);
	for (auto e : Numbers(0,10)){ 		
		std::cout << e << std::endl; 	
	}

	auto N = Numbers(0, 10);
	auto S = group_ns::sin(Numbers(0, 10));
	auto v = vec_zip(Numbers(0, 10), group_ns::sin(Numbers(0, 10)));

	auto project = to_pair();
	auto asd = project(*N.begin(), *S.begin());


	for (auto e : vec_zip(N, group_ns::sin(N))) {


		std::cout << e.first << ", " << e.second << std::endl;
	}

	for (auto e : vec_zip(Numbers(0, 5), group_ns::sin(Numbers(0, 10))) ) {
		
		
		std::cout << e.first << ", "<< e.second << std::endl;
	}
}