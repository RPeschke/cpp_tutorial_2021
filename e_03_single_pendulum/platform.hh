#ifndef platform_h__
#define platform_h__



#ifdef WIN32 
#ifndef __CINT__
#define DllExport   __declspec( dllexport )
#define __OVERIDE__ override
#else
#define DllExport   
#define __OVERIDE__ 
#endif // __CINT__
#else 
#define DllExport   
#define __OVERIDE__ 
#endif // WIN32


#ifdef _DEBUG


#define _MAKE_SHARED0(x) std::shared_ptr<x>(new x())
#define _MAKE_SHARED1(x,...) std::shared_ptr<x>(new x(__VA_ARGS__))


#else
#define _MAKE_SHARED0(x) std::make_shared<x>()
#define _MAKE_SHARED1(x,...) std::make_shared<x>(__VA_ARGS__)



#endif // _DEBUG

#ifdef WIN32
#define SCT_FUNC __FUNCSIG__
#define SCT_FUNC_SHORT  __func__
#else
#define  SCT_FUNC __PRETTY_FUNCTION__
#define SCT_FUNC_SHORT  __FUNCTION__
#endif // WIN32


#define CONCATENATE_DETAIL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_DETAIL(x, y)
#define MAKE_UNIQUE_NAME(x)  CONCATENATE(x, __LINE__)

#define  var(x)  ___set_GName( processorName_t(#x)); auto x 
#define  temp_var(x) ___set_GTemp(); ___set_GName( processorName_t(#x)); auto x 

#include <memory>


namespace ArggLib {
  namespace ArggLib_impl {

    enum _unew_ {
      __unew_start
    };

    template <typename T>
    auto operator<<(_unew_, T* in_) ->decltype(std::unique_ptr<T>(in_)) {
      return std::unique_ptr<T>(in_);
    }



    enum _Snew_ {
      __Snew_start
    };

    template <typename T>
    auto operator<<(_Snew_, T* in_) -> decltype(std::shared_ptr<T>(in_)) {
      return std::shared_ptr<T>(in_);
    }
 
  }
}

#define Unew ArggLib::ArggLib_impl::__unew_start << new 
#define Snew ArggLib::ArggLib_impl::__Snew_start << new 





#endif // platform_h__
