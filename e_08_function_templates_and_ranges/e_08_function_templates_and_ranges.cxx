#include <iostream>
#include <vector>

#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
using std::cout;


int Function_f1(int i) { // normal function with input of type integer
	return i * i;
}


double Function_f2(double i) { // normal function with input of type double
	return i+5;
}



// overload set 
int Function_f3(int i) { // normal function with input of type integer
	return i +10;
}

double Function_f3(double i) { // normal function with input of type double
	return i + 100;
}


template <typename T>
T square(T t) {
	std::cout << "  hello template  ";
	return t * t;
}


auto square(long long t) {
	std::cout << "  hello long long  ";
	return t * t;
}

template <typename T>
auto print_variable(const T& t) 
requires (requires(const T& t) {
	t.begin();
	t.end();
}) {
	
	for (const auto& e:t){
		std::cout << e << ", ";
	}
	std::cout << "\n ";
}


template <typename T>
auto print_variable(const T& t) {


	std::cout << t << "\n ";
	
}


template<class T> 
concept  is_range_v = requires (const T& t) {  t.begin(); t.end(); };



template <typename T>
auto print_variable1(const T& t) requires is_range_v<T> {
	for (const auto& e : t) {
		std::cout << e << ", ";
	}
	std::cout << "\n ";
}


template <typename T>
auto print_variable1(const T& t) {


	std::cout << t << "\n ";

}


template <is_range_v T>
auto print_variable2(const T& t) {
	for (const auto& e : t) {
		std::cout << e << ", ";
	}
	std::cout << "\n ";
}


template <typename T>
auto print_variable2(const T& t) {


	std::cout << t << "\n ";

}


using namespace ranges;



void range_test() {


	int sum = accumulate(
		views::ints(1, 5) 
		| views::transform([](int i) { return i * i;}) 
		| views::take(10),
		0);
	// prints: 385
	std::cout << sum << '\n';


	////////////////////////

	auto square1 = views::transform([](int i) { return i * i; });


	auto x = views::ints(1, 5) | square1;
	for (auto e : x){
		std::cout << e << "  ";
	}
	std::cout <<  "\n  ";
//////////////////////////////////

	auto times = views::transform([](int i, int j) { return i * j; });


	auto x1 = times(views::ints(0, 5), views::ints(5, 10));
	for (auto e : x1) {
		std::cout << e << "  ";
	}
}

int main(int argc, char** argv){

	int i = 123;
	std::cout <<i << "  "<< Function_f1(i) << std::endl;
	std::cout << i << "  " << Function_f2(i) << std::endl;

	std::cout << "\n\n";
	std::cout << i << "  " << Function_f3(i) << std::endl;
	std::cout << i << "  " << Function_f3((double)i) << std::endl;

	std::cout << "\n\n";

	std::cout <<  "double    " << square(154.0) << std::endl;
	std::cout <<  "integer   " << square(154) << std::endl;
	std::cout <<  "long long " << square(154ll) << std::endl;
	std::cout << "\n\n";



	std::vector<int> vec = { 1,2,3,4,6 };


	print_variable(vec);
	print_variable(5); 

	std::cout << "\n\n";
	print_variable1(vec);
	print_variable1(5); 

	std::cout << "\n\n";
	print_variable2(vec);
	print_variable2(5);

	range_test();
}