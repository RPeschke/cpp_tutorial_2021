#pragma once
#include <type_traits>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <iostream>
#include "group_concepts.hh"


#define yiel_return123 g_set_continue(); return

namespace group_helper {
	inline int& g_get_continue_flag() {
		thread_local static  int g_continue = 1;
		return g_continue;
	}

	inline bool g_isdone(int i) {
        return g_get_continue_flag() != i;
	}

	inline void g_reset() {
        g_get_continue_flag() = 0;
	}
	inline void g_set_continue() {
        ++(g_get_continue_flag()) ;
	}


    inline std::string root_type_name(int) {
        return "I";
    }

	inline std::string root_type_name(double) {
		return "D";
	}
	inline std::string root_type_name(float) {
		return "F";
	}

  template <class _Ty>
  using _Remove_cvref_t = std::remove_cv_t<std::remove_reference_t<_Ty>>;


  template <typename T>
  struct axis_name_t {
    T m_value = T{};

    using my_type = T;
    axis_name_t() = default;
    explicit axis_name_t(T val) : m_value(val) {}

    operator T() const
    {
      return m_value;
    }

  };

  namespace __group_imple__ {
      template <typename T>
      struct Convert_type_to_helper_vec
      {

      };
  }


#define  AXIS_NAME(name_, type_) \
  struct name_; \
  struct name_ : axis_name_t<type_> { \
    name_(type_ val) : axis_name_t<type_>(val) {}  \
    template <typename... T1>\
    name_(const std::tuple <T1...> & val) :name_( std::get<name_>(val)) {}  \
    name_() = default; \
    template <typename T1> \
    auto operator()(const T1& val) const{ \
      return std::get<name_>(val); \
    } \
    template <typename T1> \
    auto operator()(const std::vector<T1>& val) const{ \
      return select_from_range(val, ::name_());\
    } \
    template <typename... T1> \
    auto operator()(const group_vector<T1...>& val) const{ \
      return select_from_range(val, ::name_());\
    } \
    template <typename T1>\
    auto operator==(const  T1& rhs ) const -> decltype( std::get<name_>(rhs) == m_value ){\
      return std::get<name_>(rhs) == m_value ;\
    }\
  }; \
  inline std::string __get__name__(const name_&){ return #name_ ;}\
inline std::string __get__name__and_type(const name_&){ return std::string(#name_ ) +"/"+ root_type_name(type_{});}\
namespace group_helper{\
namespace __group_imple__ {\
  template <typename T>\
  struct __##name_ {\
	  auto name_() const & {\
		  const T* th = static_cast<const T*>(this);\
		  return select_from_range_sp(th->m_vec, \
            [](const auto & e) -> type_ {\
                return std::get<::name_>(e);\
            });\
	  }\
  };\
  template <>\
  struct Convert_type_to_helper_vec< name_> {\
	  template <typename T2>\
	  using myType = __##name_<T2>;\
  };\
  }}
  


  namespace __group_imple__ {
	  template <typename base_t, typename... T>
	  struct group_vector_details : group_helper::__group_imple__::Convert_type_to_helper_vec<T>::template  myType<base_t> ...
	  {

	  };
  }

  template <size_t N, typename... T>
  void  tuple_print(std::ostream& out, const std::tuple<T...>& tup) {
	  if constexpr (N < std::tuple_size<std::tuple<T...>>::value) {
		  out << __get__name__(std::get<N>(tup)) << ": " << std::get<N>(tup) << "| ";
		  tuple_print<N + 1>(out, tup);
	  }


  }
  template <typename... T>
  std::ostream& operator<<(std::ostream& out, const std::tuple<T...>& tup) {
	  out << "| ";
	  tuple_print<0>(out, tup);

	  return out;
  }

  template <typename... T>
  class group_vector : public __group_imple__::group_vector_details< group_vector<T...>, T...> {



  public:
      using element_t = std::tuple<T...>;
      using vec_t = std::vector<element_t>;
      using vec_t_sp = std::shared_ptr<std::vector<std::tuple<T...>>>;

      group_vector() {
          m_vec = std::make_shared< std::vector<std::tuple<T...>> >();
      };

      group_vector(vec_t_sp value) : m_vec(value) {}


      vec_t_sp m_vec;

	  auto begin() const {
		  return m_vec->begin();
	  }
	  auto end()const {
		  return m_vec->end();
	  }


	  auto operator[](size_t i) const {
		  return (*m_vec)[i];
	  }
	  
	  

	  template <range_container_t ROI_T>
      group_vector operator[](const ROI_T& ROI) const  {
          std::shared_ptr<std::vector<std::tuple< T...>>> ret = std::make_shared< 
                                                                                    std::vector<std::tuple<T...>>
                                                                                    >();
		  auto vec_itt = m_vec.begin();
		  auto ROI_itt = ROI.begin();
		  while (vec_itt != m_vec.end() && ROI_itt != ROI.end()) {
			  if (*ROI_itt) {
                  element_t e{};
				  ret->push_back(e);
			  }
			  ++vec_itt;
			  ++ROI_itt;
		  }

		  return ret;
	  }

	  template <range_container_t ROI_T>
      group_vector operator[](ROI_T&& ROI) const  {
          //vec_t_sp ret;
          std::shared_ptr<std::vector<std::tuple<T...> >> ret = std::make_shared<std::vector<std::tuple<T...>>>();
		  auto vec_itt = m_vec->begin();
		  auto ROI_itt = ROI.begin();
		  while (vec_itt != m_vec->end() && ROI_itt != ROI.end()) {
             
			  if (*ROI_itt) {
                
                  std::tuple<T...> e=* vec_itt;
				 ret->push_back(*vec_itt);
			  }
              
			  ++vec_itt;
              
              ++ROI_itt;
		  }

		  return group_vector(ret);
	  }
	  auto size() const {
		  return m_vec->size();
	  }

      
	  template <typename T>
	  void push_back(T&& t) {
		  m_vec->push_back(std::forward<T>(t));
      }

	  template <typename... T>
	  void emplace_back(T&&... t) {
		  m_vec->emplace_back(std::forward<T>(t)...);
	  }

  };

  template <typename... T1>
  std::ostream& operator<<(std::ostream& out, const  group_vector<T1...>& range_) {
	  for (const auto& e : range_) {
		  out << e << "\n";
	  }
	  return out;
  }

  template <range_container_t T, typename... FUNC_T>
  auto fill_group_vector(const T& inputVec, FUNC_T&& ... func)
  {

      std::shared_ptr<std::vector<std::tuple< decltype(func(inputVec[0]))...  >>> hits = std::make_shared<std::vector<std::tuple<  decltype(func(inputVec[0]))...   >>>();
	  for (const auto & e : inputVec) {
		  hits->emplace_back(func(e)...);
	  }
	  return group_vector< decltype(func(inputVec[0]))...  >(hits);
  }

  template <typename... FUNC_T>
  auto fill_group_vector(size_t s, FUNC_T&& ... func)
  {
	  std::shared_ptr<std::vector<std::tuple<  decltype(func((int)0))...  >>> hits = std::make_shared<std::vector<std::tuple<  decltype(func((int)0))...  >>>();
	  for (int i = 0; i < s; ++i) {
		  hits->emplace_back(func(i)...);
	  }
	  return group_vector<decltype(func((int)0))... >(hits);
  }

  template <typename FUNC_T>
  auto fill_group_vector2(size_t s, FUNC_T&& func)
  {
	  std::vector< decltype(func((int)0)) > hits;
	  for (int i = 0; i < s; ++i) {
		  hits.emplace_back(func(i));
	  }
	  return hits;
  }


  //////////////////////////////
  template <range_container_t T, typename... FUNC_T>
  auto fill_vector(const T& inputVec, FUNC_T&& ... func)
  {
    std::vector<std::tuple<  decltype(func(inputVec[0]))...  >> hits;
    for (int i = 0; i < inputVec.size(); ++i) {
      hits.emplace_back(func(inputVec[i])...);
    }
    return hits;
  }

  template <typename... FUNC_T>
  auto fill_vector1(size_t s, FUNC_T&& ... func)
  {
	  std::vector<std::tuple<  decltype(func((int)0))...  >> hits;
	  for (int i = 0; i < s; ++i) {
		  hits.emplace_back(func(i)...);
	  }
	  return hits;
  }

  template <typename FUNC_T>
  auto fill_vector2(size_t s, FUNC_T&&  func)
  {
	  std::vector< decltype(func((int)0)) > hits;
	  for (int i = 0; i < s; ++i) {
		  hits.emplace_back(func(i));
	  }
	  return hits;
  }
  template <typename T1, typename T2>
  class __range__impl {

  public:

    __range__impl(T1&& b, T2&& e) : m_begin(b), m_end(e) {}
    __range__impl(const T1& b, const T2& e) : m_begin(b), m_end(e) {}
    auto begin() const
    {
      return m_begin;
    }
    auto back() const
    {
      return *(m_end - 1);
    }
    auto front() const
    {
      return *(m_begin);
    }
    auto end() const
    {
      return m_end;
    }
    auto operator[](size_t i) const
    {
      return *(m_begin + i);
    }
    size_t size() const
    {
      return  m_end - m_begin;
    }
    T1 m_begin;
    T2 m_end;

  };

  template <typename... T>
  group_vector<T...>  make_group_vector(const std::vector<std::tuple<T...>>& container) {
      std::shared_ptr< std::vector<std::tuple<T...>>> ret = std::make_shared<std::vector<std::tuple<T...>>>(container);
      return   group_vector<T...>( ret );
  }
  template <typename... T>
  group_vector<T...>  make_group_vector( std::shared_ptr<std::vector<std::tuple<T...>>>& container) {
	  return   group_vector<T...>(container);
  }

  template <typename... T>
  group_vector<T...>  make_group_vector(std::tuple<T...> container);


  template <typename T1, typename T2>
  auto __range__(T1&& b, T2&& e)
  {
    return __range__impl< _Remove_cvref_t<T1>, _Remove_cvref_t<T2> >(std::forward<T1>(b), std::forward<T2>(e));
  }

  ///////////////////////


  template <typename T1, typename T2, typename T3>
  class __range__impl_with_container {

  public:

      __range__impl_with_container(T1&& b, T2&& e, T3&& t3) : m_begin(b), m_end(e), m_container(t3) {}
      __range__impl_with_container(const T1& b, const T2& e, T3 t3) : m_begin(b), m_end(e), m_container(t3){}
	  auto begin() const
	  {
		  return m_begin;
	  }
	  auto back() const
	  {
		  return *(m_end - 1);
	  }
	  auto front() const
	  {
		  return *(m_begin);
	  }
	  auto end() const
	  {
		  return m_end;
	  }
	  auto operator[](size_t i) const
	  {
		  return *(m_begin + i);
	  }
	  size_t size() const
	  {
		  return  m_end - m_begin;
	  }
	  T1 m_begin;
	  T2 m_end;

      T3 m_container;
  };

  template <typename T1, typename T2, typename T3>
  std::ostream& operator<<(std::ostream& out, const  __range__impl_with_container<T1, T2, T3>& range_) {
      for (const auto&e : range_){
          out << e << "\n";
      }
      return out;
  }


  template <typename T1, typename T2, typename T3>
  auto __range__(T1&& b, T2&& e, T3 container)
  {
	  return __range__impl_with_container< _Remove_cvref_t<T1>, _Remove_cvref_t<T2>, _Remove_cvref_t<T3> >(std::forward<T1>(b), std::forward<T2>(e), container);
  }
  template <typename T, typename Projector_T>
  struct select_itterator {

	  T m_itterator;
	  Projector_T m_pro;
	  select_itterator(T itt, Projector_T pro) :m_itterator(itt), m_pro(pro) {}



	  auto operator*() const {
		  return  m_pro(*m_itterator);
	  }



	  select_itterator& operator++() { ++m_itterator; return *this; }
	  select_itterator operator++(int) { select_itterator tmp = *this; ++(*this); return tmp; }

	  template <typename T>
	  bool operator!= (T&& t) {
		  return  bool(m_itterator != t);
	  }

  };

  template <typename RANGE_T, typename PROJECTOR_T>
  auto select_from_range(const RANGE_T& r, PROJECTOR_T&& p) {
      return  __range__(select_itterator(r.begin(), std::forward<PROJECTOR_T>(p)), r.end());
  }

  template <typename RANGE_T, typename PROJECTOR_T>
  auto select_from_range_sp(const RANGE_T& r, PROJECTOR_T&& p) {
	  return  __range__(
          select_itterator<
                            decltype(r->begin()), 
                            PROJECTOR_T>( 
                                    r->begin(), 
                                    std::forward<PROJECTOR_T>(p)
                                ), 
                            r->end(),
                       r);
  }

  template <typename RANGE_T, typename PROJECTOR_T>
  auto select_from_range_with_container(const RANGE_T& r, PROJECTOR_T&& p) {
	  return  __range__(
		  select_itterator<
		  decltype(r.begin()),
		  PROJECTOR_T>(
			  r.begin(),
			  std::forward<PROJECTOR_T>(p)
			  ),
		  r.end(),
		  r);
  }
  template <typename T1 , typename T2 ,typename T2a,  typename T3>
  auto operator==(const __range__impl_with_container<T1,T2,T2a>& r, const T3& item) {
      return select_from_range_with_container(r, [item](const auto& e) {
          return e == item; 
      });
  }
  template <typename T1, typename T2, typename T2a, typename T3>
  auto operator>=(const __range__impl_with_container<T1, T2, T2a >& r, const T3& item) {
	  return select_from_range_with_container(r, [item](const auto& e) {
		  return e >= item;
	  });
  }

  template <typename T1, typename T2, typename T2a, typename T3>
  auto operator>(const __range__impl_with_container<T1, T2, T2a>& r, const T3& item) {
	  return select_from_range_with_container(r, [item](const auto& e) {
		  return e > item;
	  });
  }

  template <typename T1, typename T2, typename T2a, typename T3>
  auto operator<(const __range__impl_with_container<T1, T2, T2a >& r, const T3& item) {
	  return select_from_range_with_container(r, [item](const auto& e) {
		  return e < item;
	  });
  }

  template <typename T1, typename T2, typename T2a, typename T3>
  auto operator<=(const __range__impl_with_container<T1, T2, T2a>& r, const T3& item) {
	  return select_from_range_with_container(r, [item](const auto& e) {
		  return e < item;
	  });
  }
  template <typename... T>
  struct group {
    template <typename VEC_T, typename T1, typename... T_rest>
    static auto   __isEequal(const VEC_T& vecA, const VEC_T& vecB) -> decltype(std::enable_if_t< (bool)sizeof...(T_rest), bool> {})
    {
      if (std::get<T1>(vecA) != std::get<T1>(vecB)) {
        return false;
      }
      return __isEequal< VEC_T, T_rest...>(vecA, vecB);
    }


    template <typename VEC_T, typename T1>
    static bool __isEequal(const VEC_T& vecA, const VEC_T& vecB)
    {
      return std::get<T1>(vecA) == std::get<T1>(vecB);
    }


	template <typename VEC_T, typename... FUNC_T>
    static auto get(const std::vector<VEC_T>& vec) {
        return apply(vec, [](const auto& rng) {
            return rng;
        });
    
    }



    template <range_container_t VEC_T, typename... FUNC_T>
    static auto apply(const VEC_T& vec, FUNC_T&& ... fun)
    {

      std::vector< std::tuple<T..., decltype(fun(__range__(vec.begin(), vec.end())))...  >> ret;
      if (vec.empty()) {
        return ret;
      }
      auto tail = std::begin(vec);

      for (auto head = std::begin(vec); head != std::end(vec); ++head) {
        if (!group<T...>::__isEequal< std::remove_cvref_t <decltype(*vec.begin())>, T...>(*head, *tail)) {
          do {
			  g_reset();
			  ret.emplace_back(std::get<T>(*tail)..., fun(__range__(tail, head))...);

          } while (!g_isdone(sizeof...(FUNC_T)) );
          tail = head;
        }
      }


      ret.emplace_back(std::get<T>(*tail)..., fun(__range__(tail, std::end(vec)))...);
      return ret;
    }

	template <range_container_t VEC_T, typename FUNC_T>
	static auto apply1(const VEC_T& vec, FUNC_T&&  fun)
	{
  
		 std::vector<  decltype(std::tuple_cat(std::tuple<T...>(), fun(__range__(vec.begin(), vec.end()))[0] ))  > ret;
	
		auto tail = vec.begin();

		for (auto head = vec.begin(); head != vec.end(); ++head) {
			if (!group<T...>::__isEequal< std::remove_cvref_t <decltype(*vec.begin())>, T...>(*head, *tail)) {
                auto dummy = fun(__range__(tail, head));
                for (const auto& d: dummy) {
                    ret.push_back( std::tuple_cat( std::make_tuple(  std::get<T>(*tail)...) , d) );
                }
				tail = head;
			}
		}

		
        auto dummy = fun(__range__(tail, std::end(vec)));
        for (const auto& d : dummy) {
			ret.push_back(std::tuple_cat(std::make_tuple(std::get<T>(*tail)...), d));
		}


        return ret;
	}

	template <range_container_t VEC_T, typename FUNC_T>
	static auto apply2(const VEC_T& vec, FUNC_T&& fun)
	{
	
		decltype(make_group_vector(
                                std::tuple_cat(
                                        std::tuple<T...>(), fun(__range__(vec.begin(), vec.end() ))
                                    )
                                )
                                )  
                     ret;

		auto tail = vec.begin();

		for (auto head = vec.begin(); head != vec.end(); ++head) {
			if (!group<T...>::__isEequal< std::remove_cvref_t <decltype(*vec.begin()) >, T...>(*head, *tail)) {
				auto dummy = fun(__range__(tail, head));

				ret.push_back(std::tuple_cat(std::make_tuple(std::get<T>(*tail)...), dummy));

				tail = head;
			}
		}


		auto dummy = fun(__range__(tail, std::end(vec)));

		ret.push_back(std::tuple_cat(std::make_tuple(std::get<T>(*tail)...), dummy));
		

		return ret;
	}


    template <typename A1 , typename... ARGGS>
    struct __get_element {

      template<class ARRAY_T>
      static constexpr auto has_safe_access(ARRAY_T&& arr) -> decltype(arr.at(0), std::true_type());
      static constexpr auto has_safe_access(...)->std::false_type;

      template <class ARRAY_T>
      static auto& get_safe_if_possible(ARRAY_T& arr, size_t i)
      {
        if constexpr(decltype(has_safe_access(arr))::value) {
          return arr.at(i);
        } else {
          return arr[i];
        }
      }



      template <typename T1, typename T2>
      static auto& get(const T1& e, T2& out_array)
      {
        if constexpr(sizeof...(ARGGS)) {
          return __get_element<ARGGS...>::get(e,
                                              get_safe_if_possible(out_array, std::get<A1>(e))
                                             );
        } else {
          return get_safe_if_possible(out_array, std::get<A1>(e));
        }
      }

    };

    template <typename T1, typename T2, typename T3, typename FUNC_T>
    static auto to_array(const  T2& in_array, T3& out_array, FUNC_T&& fun)
    {
      for (const auto& e : in_array) {
        auto& x = __get_element<T...>::get(e, out_array);
        x = fun(x, std::get<T1>(e));
      }
    }
    template <typename T1, typename T2, typename T3>
    static auto to_array(const  T2& in_array, T3& out_array)
    {
      return to_array<T1>(in_array, out_array, std::plus());
    }

  };

  template <typename CONTAINER_T, typename FUNC_T>
  void erase_remove_if(CONTAINER_T& container, FUNC_T&& fun)
  {
    container.erase(
      std::remove_if(container.begin(), container.end(),
                     std::forward<FUNC_T>(fun)),
      container.end()
    );
  }

  template <typename CONTAINER_T>
  void sort(CONTAINER_T& container)
  {
    std::sort(container.begin(), container.end());
  }

  template <typename CONTAINER_T>
  void drop_duplicates(CONTAINER_T& container)
  {
    container.erase(std::unique(container.begin(), container.end()), container.end());
  }

  struct plus {
    template<typename T, typename U>
    constexpr auto operator()(T&& t, U&& u) const -> decltype((T&&) t + (U&&) u)
    {
      return (T&&) t + (U&&) u;
    }
  };

  template<typename T1 = int>
  struct greater {
    explicit greater(T1&& data) : m_data(data) {}
    explicit greater(const T1& data) : m_data(data) {}
    T1 m_data;


    constexpr auto operator()(const T1& u) const
    {
      return m_data < u;
    }
  };

  template<typename T1>
  struct greater_equal {
    explicit greater_equal(T1 data) : m_data(data) {}

    T1 m_data;
    template<typename U>
    constexpr auto operator()(U&& u) const
    {
      return m_data <= (U&&) u;
    }
  };
  struct identity {
    template<typename T>
    constexpr T&& operator()(T&& t) const noexcept
    {
      return (T&&) t;
    }
  };


  template <typename CONTAINER_T, typename INIT_T, typename OP_T = plus, typename PROJECTION_T =  identity>
  auto accumulate(const  CONTAINER_T& container, INIT_T init, OP_T op = plus {} , PROJECTION_T proj = identity{})
  {
    for (const auto& e : container)
      init = op(init, proj(e));
    return init;
  }

  template <typename CONTAINER_T, typename OP_T = group_helper::greater<int>, typename PROJECTION_T =  identity>
  auto count_if(const  CONTAINER_T& container, OP_T op = group_helper::greater<int> {0} , PROJECTION_T proj = identity{})
  {
    int i = 0;
    for (const auto& e : container)
      if (op(proj(e)))
        ++i;
    return i;
  }

  template <typename CONTAINER_T, typename CONDITION_T, typename DEFAULT_T = int, typename PROJECTION_T =  identity>
  auto first_or_default(const  CONTAINER_T& container, const CONDITION_T& con,  DEFAULT_T default__ = 0,
                        PROJECTION_T proj = identity {})
  {
    decltype(proj(container[0])) ret = default__;
    for (const auto& e : container) {
      if (con == e) {
        return proj(e);
      }
    }
    return ret;
  }
}