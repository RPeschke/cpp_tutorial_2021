#include <iostream>
#include <functional>
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
#include "TGSignals.hh"


const double frameTime = 0.1;
const int frameFactor = 1000;
const double delta_t =0.1* frameTime / frameFactor;

class vec2d{
  public:
  vec2d(double x_ =0, double y_ =0):x(x_),y(y_){}
  double x =0,y =0;
};
class mass_object{

  vec2d m_force_old;
  vec2d velocity_old;
public:
  vec2d m_force;
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

  bool constraint_applied = false;

  void draw(TGraph& gr, int index) {
  
    gr.SetPoint(index,position.x,position.y);
  }
  void update(double i){
    if (is_fixed){
      return;
    }

    velocity.x += 0.5 * (m_force.x ) *i /mass;
    velocity.y += 0.5 * (m_force.y ) *i /mass;

    position.x += 0.5*(velocity.x )*i;
    position.y += 0.5*(velocity.y )*i;

    velocity_old = velocity;
    m_force_old = m_force;
    m_force = vec2d{};
    constraint_applied = false;
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

  virtual bool is_constraint() const { return false; }
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
  void init(TCanvas* canvas) {
	  c1 = canvas;
	  m_graph = std::make_shared<TGraph>();
  }
  void process(){
      for (int i =0;i< frameFactor ;++i) {
        simulate(delta_t);
      }
      c1->cd();
      Draw();  
      m_graph->Draw("A*");
      m_graph->GetXaxis()->SetLimits(-10,10);  
      m_graph->GetYaxis()->SetRangeUser(-10,10);  
      c1->Modified();
      c1->Update();

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



#include "gui5.hh"
#define  my_fun0(Name,Signal) void Name(std::function<void()>&& f ){ \
std::cout << Signal << std::endl; \
f(); \
  }

#define  my_fun(Name,Signal,...) void Name(std::function<void(__VA_ARGS__)>&& f ){ \
std::cout << Signal << std::endl; \
f(); \
  }

my_fun(test1, "adas",void)
//______________________________________________________________________________
int main(int argc, char **argv)
{


    auto r = __RQSignals__Internal::get_class_suffix<Int_t,Int_t>();
    auto r1 = __RQSignals__Internal::get_type_strings<Int_t, Int_t>();
    
    test1([](int i =0 ) {
        std::cout << i << std::endl;
    });
	TApplication app("myApp",&argc,argv);

  auto g1 =   gui5();
   //auto canvas = new gui4();

   RQ_signals(g1.fListBox4548).ChangedBy(
       [](char* i) {     
       std::cout << i << std::endl;  
 });
  stage s;
  s.init(g1.c135);
  auto anker = Snew mass_object();
  anker->is_fixed = true;
  s.m_masses.push_back(anker);



  auto p_mass = Snew mass_object( vec2d(1,0) );
  s.m_masses.push_back(p_mass);

  auto p_mass2 = Snew mass_object(vec2d(2,0) );
  s.m_masses.push_back(p_mass2);
  
  
  auto g      = Snew gravity(p_mass, vec2d{0,-9.81});
  s.m_forces.push_back(g);

  auto g2      = Snew gravity(p_mass2, vec2d{0,-9.81});
  s.m_forces.push_back(g2);


  auto spring_ = Snew spring(p_mass,anker, 100,1);
  s.m_forces.push_back(spring_);
  auto spring2_ = Snew spring(p_mass,p_mass2, 100,1);
  s.m_forces.push_back(spring2_);

  //auto fixed2 = Snew fixed_distance(p_mass, p_mass2, 1);
  //s.m_forces.push_back(fixed2);
  //auto fixed1 = Snew fixed_distance(anker,p_mass, 1);
  //s.m_forces.push_back(fixed1);
   
  


  //s.init();
  
  TTimer* timer = new TTimer(frameTime);

  RQ_signals(timer).Timeout([&s]() { s.process();   });

  
  timer->TurnOn();


  app.Run();
  return 0;

}
