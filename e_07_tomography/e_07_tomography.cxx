
#include <iostream>
#include "TImage.h"
#include "TH2D.h"
#include "TApplication.h"
#include "group_helper.hh"
#include "TMath.h"
#include "TCanvas.h"
#include "TBrowser.h"
#include "TTimer.h"
#include "TGSignals.hh"

using namespace group_helper;

AXIS_NAME(index_t, int);
AXIS_NAME(height, int);
AXIS_NAME(Width, int);
AXIS_NAME(Color, int);

AXIS_NAME(angle, double);
AXIS_NAME(x_axis, int);
AXIS_NAME(projection, int);
const double frameTime = 0.1;


int inRange(int x, int x_min, int x_max) {

	if (x< x_min){
		return x_min;
	}
	if (x >= x_max) {
		return x_max-1;
	}
	return x;
}
//______________________________________________________________________________
int main(int argc, char** argv)
{
	TApplication app("myApp", &argc, argv);
	TImage* img = TImage::Open("C:/Users/Richa/Documents/github/cpp_tutorial_2021/e_07_tomography/threedots.jpg");

	auto argb = img->GetArgbArray();
	int h = img->GetHeight();
	int w = img->GetWidth();

	auto df_img = fill_vector1(h * w,
		[&](auto index) -> height { return index / w; },
		[&](auto index) -> Width { return index % (w); },
		[&](auto index) -> Color { return argb[index] & 0xffffff; }
	);


	std::vector<std::tuple<angle, x_axis, projection>> df_summed;
	for (double angle_ = 0; angle_ < 180; angle_ += 1) {

		double angle_1 = TMath::DegToRad()* angle_;
		int height0 = h / 2, weight0 = w / 2;
		auto df_projection = fill_vector(df_img,
			[&](const auto& e) -> angle { return angle_; },
			[&](const auto& e) -> x_axis { return (height(e) - height0) * TMath::Cos(angle_1) - (Width(e) - weight0) * TMath::Sin(angle_1); },
			[&](const auto& e) -> projection { return Color(e); }
		);
		std::sort(df_projection.begin(), df_projection.end());
		auto df_summed_projection = group<angle, x_axis>::apply(df_projection,
			[](const auto& e) -> projection {
			return std::accumulate(
				std::begin(e), std::end(e), 0,
				[](const auto& e1, const auto& e2) {
				return e1 + projection(e2);
			});
		}
		);

		df_summed.insert(std::end(df_summed), std::begin(df_summed_projection), std::end(df_summed_projection));
	}

	int i_min = -TMath::Max(h, w);
	int i_max = TMath::Max(h, w);
	TH2D h4("h4", "h4", 1000, i_min, i_max, 100,0,180);
	TH2D h5("h5", "h5", 100, i_min, i_max, 100, i_min, i_max);



	auto c1 = new TCanvas();
	
	c1->Divide(2, 1);
	

	TTimer* timer = new TTimer(frameTime);
	auto df_grouped = group_helper::group<angle>::get(df_summed);
	int i1 = 0;
	RQ_signals(timer).Timeout([&]() { 
		
		
		const auto size_df = df_grouped.size();
		if (i1 >= size_df){
			return;
			i1 = 0;
			h4.Reset();
			h5.Reset();
		}

		
		const auto& current_angle = df_grouped[i1];
		auto df = std::get<1>(current_angle);
		for (const auto&e : df){
			h4.Fill(x_axis(e), angle(e), projection(e));
		}
		const double angle1 = -TMath::DegToRad() * angle(current_angle);
		

		for (int i = i_min; i < i_max; ++i) {
			for (int j = i_min; j < i_max; ++j) {
				double tx = TMath::Cos(angle1);
				double ty = TMath::Sin(angle1);
				double nx = TMath::Sin(angle1);
				double ny = -TMath::Cos(angle1);
				int lamda = i * tx + j * ty;
				
				auto x23 = x_axis(df[0]);
				//std::cout << angle(current_angle)<< "   "<< lamda << "   " << inRange(lamda - x23, 0, df.size())<<  "   "<< projection(df[inRange(lamda - x23, 0, df.size())])<<std::endl;
				auto x231 = projection(df[inRange(lamda - x23,0,df.size()) ]);
				if (x231 >0 ){
					h5.Fill(i, j, x231);
				}

			}
		}
		
		
		++i1;
		


		c1->cd(1);
		h4.Draw();
		
		c1->cd(2);
		h5.Draw("colz");

		c1->Modified();
		c1->Update();


	});
	

	timer->TurnOn();
	app.Run();
}