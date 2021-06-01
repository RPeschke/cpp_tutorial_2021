#ifndef RQSignals_h__
#define RQSignals_h__
#include <string>
#include <memory>
#include <vector>
#include "TThread.h"



template <typename T>
auto RQ_signals(std::shared_ptr<T>& obj) {
	return RQ_signals(obj.get());
}
template <typename T>
auto RQ_signals(std::unique_ptr<T>& obj) {
	return RQ_signals(obj.get());
}
template <typename T>
auto _RQ_slots(std::shared_ptr<T>& obj) {
	return _RQ_slots(obj.get());
}
template <typename T>
auto _RQ_slots(std::unique_ptr<T>& obj) {
	return _RQ_slots(obj.get());
}



#define  __DEFINE_RQ_SIGNAL__(funName,SignalString) /*emits SignalString*/ \
RQ_SIGNAL_TEMPLATE<T>  funName() { \
return RQ_SIGNAL_TEMPLATE<T>(this->m_object, SignalString, this->cname.Data()); \
  }

#define  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(derivedname,baseName) derivedname<T>(T* obj, const char* ClassName) :baseName<T>(obj, ClassName) 


#define  __DEFINE_RQ_SIGNAL__FACTORY(ClassName,ClassSignalName) class ClassName;\
 inline ClassSignalName<ClassName> RQ_signals(ClassName* obj) {\
  return ClassSignalName<ClassName>(obj, #ClassName);\
}\
inline ClassSignalName<ClassName> RQ_signals(ClassName& obj) {\
  return ClassSignalName<ClassName>(&obj, #ClassName);\
}


#define START__DEFINE_RQ_SIGNAL_BASE_CLASS(CLASSNAME) class CLASSNAME; \
template <typename T> \
class CLASSNAME##_signals{ \
public: \
TString cname; \
T* m_object; \
 CLASSNAME##_signals(T* obj, const char* ClassName) : m_object(obj), cname(ClassName) {}

#define START__DEFINE_RQ_SIGNAL_DERIVED_CLASS(CLASSNAME,BASE_CLASS) class CLASSNAME; \
template <typename T> \
class  CLASSNAME##_signals : public BASE_CLASS##_signals<T> {\
public: \
 CLASSNAME##_signals<T>(T* obj, const char* ClassName) : BASE_CLASS##_signals<T>(obj, ClassName){}

#define  END__DEFINE_RQ_SIGNAL_CLASS(CLASSNAME) };\
 inline CLASSNAME##_signals<CLASSNAME> RQ_signals(CLASSNAME* obj) {\
  return CLASSNAME##_signals<CLASSNAME>(obj, #CLASSNAME);\
}\
inline CLASSNAME##_signals<CLASSNAME> RQ_signals(CLASSNAME& obj) {\
  return CLASSNAME##_signals<CLASSNAME>(&obj, #CLASSNAME);\
}


#define START__DEFINE_RQ_SLOTS_BASE_CLASS(CLASSNAME) class CLASSNAME; \
template <typename T> \
class CLASSNAME##_slots{ \
public: \
TString cname; \
T* m_object; \
 CLASSNAME##_slots(T* obj, const char* ClassName) : m_object(obj), cname(ClassName) {}


#define START__DEFINE_RQ_SLOTS_DERIVED_CLASS(CLASSNAME,BASE_CLASS) class CLASSNAME; \
template <typename T> \
class  CLASSNAME##_slots : public BASE_CLASS##_slots<T> {\
public: \
 CLASSNAME##_slots<T>(T* obj, const char* ClassName) : BASE_CLASS##_slots<T>(obj, ClassName){}

#define  END__DEFINE_RQ_SLOTS_CLASS(CLASSNAME) };\
 inline CLASSNAME##_slots<CLASSNAME> _RQ_slots(CLASSNAME* obj) {\
  return CLASSNAME##_slots<CLASSNAME>(obj, #CLASSNAME);\
}\
 inline CLASSNAME##_slots<CLASSNAME> _RQ_slots(CLASSNAME& obj) {\
  return CLASSNAME##_slots<CLASSNAME>(&obj, #CLASSNAME);\
}

#define __DEFINE_RQ_SLOT__(funName,SignalString)  \
RQ_SLOT_TEMPLATE<T>  funName() { \
return RQ_SLOT_TEMPLATE<T>(m_object, SignalString, cname.Data()); \
  }

#define  __DEFINE_RQ_SLOT__CONSTRUCTOR(derivedname,baseName) derivedname<T>(T* obj, const char* ClassName) :baseName<T>(obj, ClassName) 

#define  __DEFINE_RQ_SLOT__FACTORY(ClassName,ClassSignalName) inline ClassSignalName<ClassName> _RQ_slots(ClassName* obj) {\
  return ClassSignalName<ClassName>(obj, #ClassName);\
}\
inline ClassSignalName<ClassName> _RQ_slots(ClassName& obj) {\
  return ClassSignalName<ClassName>(&obj, #ClassName);\
}

template <typename T>
class RQ_SLOT_TEMPLATE {
public:
  RQ_SLOT_TEMPLATE(T* obj, const std::string& str, const std::string& class_name = "") :
	m_object(obj),
	m_name(str),
	m_className(class_name) {}

  T* m_object;
  std::string m_name, m_className;
};

template <typename T>
class RQ_SIGNAL_TEMPLATE :public RQ_SLOT_TEMPLATE<T> {
public:
  RQ_SIGNAL_TEMPLATE(T* obj, const std::string& str, const std::string& class_name = "") :RQ_SLOT_TEMPLATE<T>(obj, str, class_name) {}
};

template <typename T>
RQ_SIGNAL_TEMPLATE<T> __make_RQsignal(T* obj, const std::string& member, const std::string& class_name) {
  return RQ_SIGNAL_TEMPLATE<T>(obj, member, class_name);
}
template <typename T>
RQ_SIGNAL_TEMPLATE<T> __make_RQsignal(T* obj, const std::string& member) {
  return __make_RQsignal(obj, member, obj->Class_Name());
}

template <typename T>
RQ_SLOT_TEMPLATE<T> __make_RQslot(T* obj, const std::string& member) {
  return __make_RQsignal(obj, member);
}
template <typename T>
RQ_SLOT_TEMPLATE<T> __make_RQslot(T* obj, const std::string& member, const std::string& class_name) {
  return __make_RQsignal(obj, member, class_name);
}
template <typename T1, typename T2>
void operator >> (const RQ_SIGNAL_TEMPLATE<T1>& signal_, const RQ_SLOT_TEMPLATE<T2>& slot_) {

  signal_.m_object->Connect(signal_.m_name.c_str(), slot_.m_className.c_str(), slot_.m_object, slot_.m_name.c_str());
}


namespace __RQSignals__Internal {
	using Pointer_Int_t = long long;

	class defineOnConstruction {
	public:

		defineOnConstruction(std::string code) {
			static  std::vector<std::string> m_def;
			if (std::find(m_def.begin(), m_def.end(), code) != m_def.end()) {
				return;
			}
			m_def.push_back(code);
			//std::cout << code << std::endl;
			gInterpreter->Declare(code.c_str());
		}

	};


	class RQ_Slot_lamda {
	public:
		RQ_Slot_lamda() {
			static  defineOnConstruction adc{
				R"123(
using pointer_int_t_r = long long;
	class TQ_common_slots  { 
		public:
		TQ_common_slots(pointer_int_t_r obj){
			m_ptr = (void*)obj;
		}
		virtual ~TQ_common_slots(){ }

		void* m_ptr; 


		ClassDef(TQ_common_slots, 0)
	}; )123"
			};

		}

		virtual ~RQ_Slot_lamda() {}

		virtual RQ_Slot_lamda* move_to_heap() = 0;
		virtual std::string  get_function_pointer() = 0;


		virtual std::string  get_TQ_className() = 0;
		virtual std::string  get_TQ_slot() = 0;
	};



	std::string create_TQ_class(std::string TQ_classs_name, std::vector<std::string> arguments_t) {
		std::string args;
		std::string argsCALL;
		std::string start;
		std::string f_type = "void(*)(void*";
		int i = 0;
		for (auto& e : arguments_t) {
			args += start + e + "  x" + std::to_string(i);
			start = ", ";
			f_type += ", " + e;
			argsCALL += ",  x" + std::to_string(i);
		}
		f_type += ")";

		return std::string("class ") + TQ_classs_name + R"123( : public TQ_common_slots {
			public:
				using f_type = )123" + f_type + R"123(;
				 )123" + TQ_classs_name + R"123((pointer_int_t_r fun, pointer_int_t_r obj) : TQ_common_slots(obj) {
					m_f2 = (f_type)fun;
				}
				f_type m_f2;
				void slot()123" + args + R"123( ){
					m_f2(m_ptr)123" + argsCALL + R"123(  );
				}
				ClassDef()123" + TQ_classs_name + ", 0) }; ";

	}



	template <typename T, typename... ARGS>
	void RQ_Slot_lamda_slot(void* ptr, ARGS... i) {
		T* slot = (T*)ptr;
		slot->m_f(i...);
	}

	template <typename T>
	class __type_to_string {
	public:
		static std::string get_string() {
			return "Not implemented";
		}
	};


	template <>
	class __type_to_string<Int_t> {
	public:
		static std::string get_string() {
			return "Int_t";
		}
	};
}

class RQ_Slot_void : public __RQSignals__Internal::RQ_Slot_lamda {
public:
	std::function<void()> m_f;
	std::string m_TQ_classs_name = "TQ_common_slots_void";

	template <typename T>
	RQ_Slot_void(T&& t) :m_f(std::forward<T>(t)) {

		static __RQSignals__Internal::defineOnConstruction abc{

			__RQSignals__Internal::create_TQ_class(m_TQ_classs_name,  {})

		 };
	}
	virtual RQ_Slot_lamda* move_to_heap()  override {
		return new RQ_Slot_void(std::move(m_f));
	}
	void slot_void() {
		m_f();
	}
	virtual std::string get_function_pointer() {
		return std::to_string((__RQSignals__Internal::Pointer_Int_t)__RQSignals__Internal::RQ_Slot_lamda_slot<RQ_Slot_void>);
	}
	virtual std::string  get_TQ_className() {
		return "TQ_common_slots_void";
	}
	virtual std::string  get_TQ_slot() {
		return "\"slot()\"";
	}
};







template <typename ARG_T>
class RQ_Slot : public __RQSignals__Internal::RQ_Slot_lamda {
public:


	std::function<void(ARG_T)> m_f;
	std::string m_TQ_classs_name = "TQ_common_slots_";
	std::vector<std::string> arguments_t = { __RQSignals__Internal::__type_to_string<ARG_T>::get_string() };
	template <typename T>
	RQ_Slot(T&& t) :m_f(std::forward<T>(t)) {
		m_TQ_classs_name += __RQSignals__Internal::__type_to_string<ARG_T>::get_string();
		static __RQSignals__Internal::defineOnConstruction abc{
			__RQSignals__Internal::create_TQ_class(m_TQ_classs_name, arguments_t)
		 };
	}
	virtual __RQSignals__Internal::RQ_Slot_lamda* move_to_heap()  override {
		return new RQ_Slot(std::move(m_f));
	}

	virtual std::string get_function_pointer() {
		return std::to_string((__RQSignals__Internal::Pointer_Int_t)__RQSignals__Internal::RQ_Slot_lamda_slot<RQ_Slot<ARG_T>,  ARG_T>);
	}

	virtual std::string  get_TQ_className() {
		return m_TQ_classs_name;
	}
	virtual std::string  get_TQ_slot() {
		std::string ret = "\"slot(";
		std::string start = "";
		for (auto& e : arguments_t) {
			ret += start + e;
			start = ", ";
		}
		ret += ")\"";
		return ret;
	}



};








template <typename T1>
void operator >> (const RQ_SIGNAL_TEMPLATE<T1>& signal_, __RQSignals__Internal::RQ_Slot_lamda&& slot_) {

	auto slot_ptr = slot_.move_to_heap();//leak 
	std::string code3 =
		signal_.m_className + "* obj = (" + signal_.m_className + "*)" + std::to_string((__RQSignals__Internal::Pointer_Int_t)signal_.m_object) + ";" +
		"{ auto* sl = new " + slot_ptr->get_TQ_className() + "(" + slot_ptr->get_function_pointer() + ", " + std::to_string((__RQSignals__Internal::Pointer_Int_t)slot_ptr) + ");" +
		"obj->Connect(\"" + signal_.m_name + "\", \"" + slot_ptr->get_TQ_className() + "\", sl, " + slot_ptr->get_TQ_slot() + ");}";// +



	//std::cout << code3 << std::endl;
	gInterpreter->ProcessLine(code3.c_str());


}


#endif // RQSignals_h__