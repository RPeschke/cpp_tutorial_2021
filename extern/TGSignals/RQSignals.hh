#ifndef RQSignals_h__
#define RQSignals_h__
#include <string>
#include <memory>
#include <vector>



template <typename T>
auto _RQ_signals(std::shared_ptr<T>& obj) {
  return _RQ_signals(obj.get());
}
template <typename T>
auto _RQ_signals(std::unique_ptr<T>& obj) {
  return _RQ_signals(obj.get());
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
return RQ_SIGNAL_TEMPLATE<T>(m_object, SignalString, cname.Data()); \
  }

#define  __DEFINE_RQ_SIGNAL__CONSTRUCTOR(derivedname,baseName) derivedname<T>(T* obj, const char* ClassName) :baseName<T>(obj, ClassName) 


#define  __DEFINE_RQ_SIGNAL__FACTORY(ClassName,ClassSignalName) class ClassName;\
 inline ClassSignalName<ClassName> _RQ_signals(ClassName* obj) {\
  return ClassSignalName<ClassName>(obj, #ClassName);\
}\
inline ClassSignalName<ClassName> _RQ_signals(ClassName& obj) {\
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
 inline CLASSNAME##_signals<CLASSNAME> _RQ_signals(CLASSNAME* obj) {\
  return CLASSNAME##_signals<CLASSNAME>(obj, #CLASSNAME);\
}\
inline CLASSNAME##_signals<CLASSNAME> _RQ_signals(CLASSNAME& obj) {\
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


class RQ_Slot_lamda;
class RQ_Slot_lamda {
public:
	bool Conection_is_alive = true;
	std::function<void()> m_f;
	template <typename T>
	RQ_Slot_lamda(T&& t) :m_f(std::forward<T>(t)) {

	}
	RQ_Slot_lamda* move_to_heap() {
		return new RQ_Slot_lamda(std::move(m_f));
	}
	void slot_void() {
		m_f();
	}

};

inline void RQ_Slot_lamda_slot_void(void* ptr) {
	RQ_Slot_lamda* slot = (RQ_Slot_lamda*)ptr;
	slot->slot_void();
}


class ROOT_Declare_once {
public:
	ROOT_Declare_once(std::string declaration) {

		gInterpreter->Declare(declaration.c_str());
	}
	std::vector<RQ_Slot_lamda*> m_ptrs;
};


template <typename T1>
void operator >> (const RQ_SIGNAL_TEMPLATE<T1>& signal_, RQ_Slot_lamda&& slot_) {
	static ROOT_Declare_once classdec(
		"class TQ_common_slots; class TQ_common_slots  { public: static std::vector<TQ_common_slots*> m_slots; using f_t = void(*)(void*);  f_t m_f2; void* m_ptr; void slot_void() { m_f2(m_ptr); }    ClassDef(TQ_common_slots, 0)}; "
	);
	RQ_Slot_lamda* slot_ptr = slot_.move_to_heap();
	classdec.m_ptrs.push_back(slot_ptr);
	std::string code3 =
		signal_.m_className + "* obj = (" + signal_.m_className + "*)" + std::to_string((long long)signal_.m_object) + ";" +
		"TQ_common_slots* sl = new TQ_common_slots();" +
		"sl->m_f2 = (void(*)(void*))" + std::to_string((long long)RQ_Slot_lamda_slot_void) + ";" +
		"sl->m_ptr = (void*)" + std::to_string((long long)slot_ptr) + ";" +
		"obj->Connect(\"" + signal_.m_name + "\", \"TQ_common_slots\", sl, \"slot_void()\");";


	gInterpreter->ProcessLine(code3.c_str());

}


#endif // RQSignals_h__