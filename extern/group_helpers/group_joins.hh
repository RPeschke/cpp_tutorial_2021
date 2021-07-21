#pragma  once 
#include <vector>
#include <utility>
#include <tuple>

struct to_pair
{
	template<typename T1, typename T2>
	constexpr auto operator()(T1&& t1, T2&& t2) const noexcept
	{
		return std::make_pair(t1, t2);
	}
};

struct to_tuple
{
	template<typename T1, typename T2>
	constexpr auto operator()(T1&& t1, T2&& t2) const noexcept
	{
		return std::make_tuple(t1, t2);
	}
};

template <typename T1, typename T2, typename projecttion_t = to_pair>
auto vec_zip(const T1& t1, const  T2& t2, projecttion_t project = to_pair()) {

	std::vector<  decltype(project(*t1.begin(), *t2.begin()))  > ret;

	auto t1_itt = t1.begin();
	auto t2_itt = t2.begin();
	while (t1_itt != t1.end() && t2_itt != t2.end()) {
		ret.push_back(project(*t1_itt, *t2_itt));
		++t1_itt;
		++t2_itt;
	}
	return ret;

}


template <typename T>
struct rhs
{
	T value;
	using my_type = typename T::my_type;
	rhs(T&& v) : value(std::move(v)) {}
	rhs(const T& v) : value(std::move(v)) {}

	template <typename T1, typename T2>
	rhs(const std::pair<T1, T2>& v): value(v.first) {

	}

	operator my_type() const {
		return (my_type)value;
	}
};

template <typename T>
struct lhs
{
	T value;
	using my_type = typename T::my_type;
	lhs(T&& v) : value(std::move(v)) {}
	lhs(const T& v) : value(std::move(v)) {}

	template <typename T1, typename T2>
	lhs(const std::pair<T1, T2>& v) : value(v.second) {

	}

	operator my_type() const {
		return (my_type)value;
	}
};