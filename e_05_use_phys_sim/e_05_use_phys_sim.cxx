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
#include "e_05_second_file.hh"


using namespace phys_sim;


//______________________________________________________________________________
int main(int argc, char **argv)
{


	TApplication app("myApp",&argc,argv);
    
  auto s = second_simulation();
  s->max_point.x = 25;
  s->max_point.y = 1;
  s->min_point.y = -1;
  
 // second_simulation();
  app.Run();
  return 0;

}
