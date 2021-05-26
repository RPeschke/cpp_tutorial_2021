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
#include "phys_sim.hh"

using namespace phys_sim;



stage* second_simulation(){
    auto  s = new stage();
    
double g_constant =0;// 9.81;
    auto anker = std::make_shared<mass_object>();
    anker->is_fixed = true;
    s->m_masses.push_back(anker);

std::shared_ptr<mass_object> last = anker;
double i =1 ;
double i_max = 100;
double r_range = 20;
double spring_constant = 1000;
double spring_length = 0.8*r_range/i_max;
for (; i < i_max ; i += 1){
    auto p_mass = std::make_shared<mass_object>(
    vec2d(i/i_max*r_range,0)
  );
  
  if( int(i) == int(i_max)/2){
   last->velocity.y = 10;
  }
  auto g  = std::make_shared<gravity>(p_mass, vec2d{0,-g_constant});
  auto spring_ = std::make_shared<spring>(p_mass,last, spring_constant,spring_length);

  s->m_masses.push_back(p_mass);
  s->m_forces.push_back(g);
  s->m_forces.push_back(spring_);
  last = p_mass;

}

    auto anker1 = std::make_shared<mass_object>(vec2d(i/i_max*r_range,0));
    anker1->is_fixed = true;
    auto spring_1 = std::make_shared<spring>(anker1,last, spring_constant,spring_length);
    s->m_masses.push_back(anker1);
    s->m_forces.push_back(spring_1);



  std::cout<< "Animate " << (int64)Animate << " stage " << (int64)&s <<std::endl;
  std::string code = "void update(){  ((void(*)(void*))" +std::to_string((int)Animate) +")( (void*)" +std::to_string((int)s)+ ");  }";
  std::cout << code <<std::endl;
    
  gInterpreter->Declare(code.c_str());
  s->init();
  
  TTimer *timer = new TTimer(s->m_delta_t*1000);
  timer->SetCommand("update()");
  timer->TurnOn();
  return s;
}