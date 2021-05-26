#pragma once

#include "TMath.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TTimer.h"
#include "TAxis.h"
#include "TApplication.h"
#include "TSystem.h"

namespace phys_sim{


class vec2d{
  public:
  double x =0,y =0;
};
class mass_object{

  vec2d m_force;
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
    velocity.x += m_force.x*i;
    velocity.y += m_force.y*i;

    position.x += velocity.x*i;
    position.y += velocity.y*i;


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
  vec2d min_point = vec2d(-10,-10),max_point=vec2d(10,10);
  double m_delta_t = 0.01;
  int draw_counter = 0;
  int draw_counter_max = 10;
  std::shared_ptr<TGraph> m_graph;
  TCanvas* c1;
  void init(){
    c1 = new TCanvas();
    m_graph = std::make_shared<TGraph>();
  }
  void process(){
      simulate(m_delta_t);
      if (++draw_counter < draw_counter_max){
        return;
      }
      Draw();  
      m_graph->Draw("A*");
      m_graph->GetXaxis()->SetLimits(min_point.x,max_point.x);  
      m_graph->GetYaxis()->SetRangeUser(min_point.y,max_point.y);  
      c1->Modified();
      c1->Update();

  }
  TCanvas* run(){
    init();
    for (int i =0 ;i < 100000; i++) {
      process();
      gSystem->Sleep(m_delta_t*1000);
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


inline void Animate(void * ptr){
  stage* s = (stage*)ptr;
  s->process();
}

}