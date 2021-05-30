#include <iostream>

#include "TMath.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TTimer.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TSystem.h"
#include "platform.hh"
#include "TQ_common_slots.hh"
#include "TGSignals.hh"

const double frameTime = 0.1;
const int frameFactor = 100000;
const double delta_t = frameTime / frameFactor;

class vec2d{
  public:
  vec2d(double x_ =0, double y_ =0):x(x_),y(y_){}
  double x =0,y =0;
};
class mass_object{

  vec2d m_force;
  vec2d m_force_old;
  vec2d velocity_old;
public:
  mass_object( vec2d Initial_position =vec2d(), vec2d initial_velocity = vec2d(),double mass_ = 1, bool is_fixed_ = false)
    : mass(mass_), 
    position(Initial_position), 
    velocity(initial_velocity), 
    is_fixed(is_fixed_){


  }

  double mass = 0;
  vec2d position;
  vec2d velocity;
  
  bool is_fixed = false;


  void draw(TGraph& gr, int index) {
  
    gr.SetPoint(index,position.x,position.y);
  }
  void update(double i){
    if (is_fixed){
      return;
    }

    velocity.x += 0.5 * (m_force.x + m_force_old.x) *i /mass;
    velocity.y += 0.5 * (m_force.y + m_force_old.y) *i /mass;

    position.x += 0.5*(velocity.x + velocity_old.x)*i;
    position.y += 0.5*(velocity.y + velocity_old.y)*i;

    velocity_old = velocity;
    m_force_old = m_force;
    m_force = vec2d{};
  }
  void add_force(vec2d Force_){
    m_force.x += Force_.x;
    m_force.y += Force_.y;
  }
};

class forces{
  protected:
  std::shared_ptr<mass_object> m_m1,m_m2;
  public:
  forces(std::shared_ptr<mass_object> m1, std::shared_ptr<mass_object> m2) :
    m_m1(std::move(m1)),m_m2(std::move(m2)){

  }
  
  virtual void apply_force() = 0;

};
class gravity:public forces{
  vec2d m_force;
public:
  gravity(std::shared_ptr<mass_object> m1, vec2d force): forces(m1, nullptr) , m_force(force) {}
  virtual void apply_force() {
    m_m1->add_force(m_force);
  }
};

class spring:public forces{
  double m_spring_constant;
  double m_length0;
public:
  spring(std::shared_ptr<mass_object> m1, std::shared_ptr<mass_object> m2,double spring_constant,double length0) 
    :forces(m1, m2), 
    m_spring_constant(spring_constant),
    m_length0(length0) {

    }
  virtual void apply_force() {
    vec2d distance;
    distance.x = m_m1->position.x - m_m2->position.x ;
    distance.y = m_m1->position.y - m_m2->position.y ;

    auto l = TMath::Sqrt( distance.x*distance.x + distance.y* distance.y );
    auto d_l = l - m_length0;
    vec2d force (
      distance.x/l * d_l*m_spring_constant,
      distance.y/l * d_l*m_spring_constant
    ) ;

    m_m2->add_force(force);
    force.x *= -1;
    force.y *= -1;
    m_m1->add_force(force);
  }
};

class stage{
  public:
  std::shared_ptr<TGraph> m_graph;
  TCanvas* c1;
  void init(){
    c1 = new TCanvas();
    m_graph = std::make_shared<TGraph>();
  }
  void process(){
      for (int i =0;i< frameFactor ;++i) {
        simulate(delta_t);
      }
      Draw();  
      m_graph->Draw("A*");
      m_graph->GetXaxis()->SetLimits(-10,10);  
      m_graph->GetYaxis()->SetRangeUser(-10,10);  
      c1->Modified();
      c1->Update();

  }
  TCanvas* run(){
    init();
    for (int i =0 ;i < 100000; i++) {
      process();
      gSystem->Sleep(10);
    }
    return c1;
  }
   void Draw(){
    int index =0;
    for(auto& e: m_masses){
      e->draw(*m_graph, index);
      index++;

    }

  }

  void simulate(double i){
    for (auto & e: m_forces){
      e->apply_force();
    }
    for(auto& e: m_masses){
      e->update(i);
    }

  }
  std::vector<std::shared_ptr<forces>> m_forces;
  std::vector<std::shared_ptr<mass_object>> m_masses;
};


void Animate(void * ptr){
  stage* s = (stage*)ptr;
  s->process();
}

//class RQ_Slot_lamda;
//class RQ_Slot_lamda {
//public:
//    std::function<void()> m_f;
//    template <typename T>
//    RQ_Slot_lamda(T&& t) :m_f(std::forward<T>(t)){
//
//    }
//    RQ_Slot_lamda* move_to_heap() {
//        return new RQ_Slot_lamda(std::move(m_f));
//    }
//    void slot_void() {
//        m_f();
//    }
//
//};
//
//void RQ_Slot_lamda_slot_void(void* ptr) {
//    
//    std::cout << "RQ_Slot_lamda_slot_void\n";
//    RQ_Slot_lamda* slot = (RQ_Slot_lamda*)ptr;
//    slot->slot_void();
//}
//
//
//class ROOT_Declare_once {
//public:
//    ROOT_Declare_once(std::string declaration) {
//		std::cout << declaration << std::endl;
//		gInterpreter->Declare(declaration.c_str());
//    }
//};
//template <typename T1>
//void operator >> (const RQ_SIGNAL_TEMPLATE<T1>& signal_,  RQ_Slot_lamda& slot_) {
//    static ROOT_Declare_once classdec(
//        "class TQ_common_slots  { public: using f_t = void(*)(void*);  f_t m_f2; void* m_ptr; void slot_void() { m_f2(m_ptr); std::cout << \"void\" << std::endl;  }    ClassDef(TQ_common_slots, 0)}; "
//    );
//    RQ_Slot_lamda* slot_ptr = slot_.move_to_heap();
//    std::string code3 = 
//        signal_.m_className +"* obj = ("+signal_.m_className+"*)" + std::to_string((long long)signal_.m_object) + ";" +
//        "TQ_common_slots* sl = new TQ_common_slots();"+
//        "sl->m_f2 = (void(*)(void*))"+ std::to_string ( (long long)RQ_Slot_lamda_slot_void) +";"+
//        "sl->m_ptr = (void*)" + std::to_string((long long)slot_ptr) + ";" +
//        "obj->Connect(\"" + signal_.m_name+"\", \"TQ_common_slots\", sl, \"slot_void()\");";
//
//    std::cout << code3 << std::endl;
//    gInterpreter->ProcessLine(code3.c_str());
//    //signal_.m_object->Connect(signal_.m_name.c_str(), slot_.m_className.c_str(), slot_.m_object, slot_.m_name.c_str());
//}

//______________________________________________________________________________
int main(int argc, char **argv)
{


	TApplication app("myApp",&argc,argv);
    
  auto anker = std::make_shared<mass_object>();
  anker->is_fixed = true;

  auto p_mass = std::make_shared<mass_object>(
    vec2d(1,0)
  );

  auto p_mass2 = std::make_shared<mass_object>(
    vec2d(2,0)
  );
  
  
  auto g      = Snew gravity(p_mass, vec2d{0,-9.81});
  auto g2      = Snew gravity(p_mass2, vec2d{0,-9.81});
  auto spring_ = Snew spring(p_mass,anker, 100,1);
  auto spring2_ = Snew spring(p_mass,p_mass2, 100,1);
  stage s;
  s.m_masses.push_back(anker);
  s.m_masses.push_back(p_mass);
  s.m_masses.push_back(p_mass2);
  s.m_forces.push_back(g);
  s.m_forces.push_back(g2);
  s.m_forces.push_back(spring_);
  s.m_forces.push_back(spring2_);

  std::cout<< "Animate " << (long long)Animate << " stage " << (long long)&s <<std::endl;
  std::string code = "void update(){  ((void(*)(void*))" +std::to_string((long long)Animate) +")( (void*)" +std::to_string((long long)&s)+ ");  }";
  std::cout << code <<std::endl;
    
  gInterpreter->Declare(code.c_str());

  //std::string code1 = "class TQ_common_slots  { public: using f_t = void(*)(void*);  f_t m_f2; void* m_ptr; void slot_void() { m_f2(m_ptr); std::cout << \"void\" << std::endl;  }    ClassDef(TQ_common_slots, 0)}; ";
  //std::cout << code1 << std::endl;
  //gInterpreter->Declare(code1.c_str());
  s.init();
  std::string code2 = "std::cout << \"hello world\" <<std::endl ;";
      std::cout << code2 << std::endl;
  gInterpreter->ProcessLine(code2.c_str());


  TTimer* timer = new TTimer(frameTime);

  std::string code3 = "TTimer* obj = (TTimer*)" + std::to_string((long long)timer) + "; TQ_common_slots* sl = new TQ_common_slots(); obj->Connect(\"Timeout()\", \"TQ_common_slots\", sl, \"slot_void()\");";
  //std::string code3 = "TQ_common_slots* sl = new TQ_common_slots(); sl->slot_void();";
  std::cout << code3 << std::endl;
  //gInterpreter->ProcessLine(code3.c_str());
  //timer->Connect("Timeout()", "TQ_common_slots", sl, "slot_void()");
  _RQ_signals(timer).Timeout() >> RQ_Slot_lamda([&s]() {

      s.process();

  });
  
  
 // timer->SetCommand("update()");
  timer->TurnOn();
  app.Run();
  return 0;

}
