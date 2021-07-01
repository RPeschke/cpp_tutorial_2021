
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
#include < utility >
#include  <type_traits>

#include "group_helper.hh"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include "TMath.h"
#include <bitset>
#include "TApplication.h"
#include <fstream>
#include <charconv>
#include "TGraph.h"
#include "TTimer.h"
#include "TCanvas.h"

using namespace group_helper;
AXIS_NAME(x_t, double);
AXIS_NAME(y_t, double);


AXIS_NAME(frequency_t, double);


std::vector<std::string_view> split_string(std::string_view line) {
	
	std::vector<std::string_view> ret;
	auto it = line.find(',');
	while (it < line.size()) {
		ret.push_back(line.substr(0, it));
		line = line.substr(it+1);
		it = line.find(',');
	}
	ret.push_back(line);
	return ret;
}

double to_double(std::string_view line) {
	double dbl;
	auto result = std::from_chars(line.data(), line.data() + line.size(), dbl);
	return dbl;
}

template <typename... ARGS>
auto load_vector(std::string inFile) {
	std::vector<std::tuple<ARGS...>> ret;
	std::string buff;
	//char buff[100];
	std::ifstream in(inFile);
	in >> buff;
	while (in){
		in >> buff;
		auto x = split_string(buff);
		ret.emplace_back(x_t(to_double(x[0])),y_t(to_double(x[1])));
	}

	return ret;
}


void draw_input_signal(std::string fileName) {

}

template <typename XAxis_t, typename YAsis_t, typename VEC_t>
std::shared_ptr<TGraph> to_TGraph(const VEC_t& vec) {
	auto ret = std::make_shared<TGraph>();

	for (const auto &e: vec){
		ret->SetPoint(ret->GetN(), XAxis_t(e), YAsis_t(e));
	}
	return  ret;
}

template <typename t1, typename T>
auto mean(const T& vec) {
	
	double ret = 0;
	for (const auto& e: vec){
		ret += t1(e);
	}
	return ret / vec.size();
}

void ex01(int argc, char** argv) {
	TApplication app("myApp", &argc, argv);
	auto df1 = fill_vector1(100,
		[&](auto index) -> x_t { return index; },
		[&](auto index) -> y_t { return TMath::Sin(index) + 10; }

	);
	auto df0 = fill_vector1(100,
		[&](auto index) -> x_t { return TMath::Cos(index / 10.0); },
		[&](auto index) -> y_t { return TMath::Sin(index / 10.0); }

	);

	auto c1 = new TCanvas();


	auto g0 = to_TGraph<x_t, y_t>(df0);
	g0->Draw("AC");
	g0->SetLineColor(3);

	int index_max = 1;
	TTimer* timer = new TTimer(100);
	RQ_signals(timer).Timeout([&]() {
		auto df1 = fill_vector1(++index_max,
			[&](auto index) -> x_t { return TMath::Cos(index / 10.0); },
			[&](auto index) -> y_t { return TMath::Sin(index / 10.0); }

		);
		auto x_mean = mean<x_t>(df1);
		auto y_mean = mean<y_t>(df1);

		auto g_mean = std::make_shared<TGraph>();
		g_mean->SetPoint(0, x_mean, y_mean);
		auto g = to_TGraph<x_t, y_t>(df1);
		g0->Draw("AC");
		g->Draw("same*");
		g_mean->Draw("same*");
		g_mean->SetMarkerColor(2);

		c1->Modified();
		c1->Update();
	});
	timer->TurnOn();
	app.Run();
}


void ex02(int argc, char** argv) {
	TApplication app("myApp", &argc, argv);

	const double Signal_frequency = 0.2;
	const double circle_frequency = 0.09;

	auto df0 = fill_vector1(100,
		[&](auto index) -> x_t { return TMath::Cos(index / 10.0); },
		[&](auto index) -> y_t { return TMath::Sin(index / 10.0); }

	);

	auto g_mean_tail = std::make_shared<TGraph>();

	auto c1 = new TCanvas();

	c1->Divide(2, 1);
	c1->cd(2);
	auto g0 = to_TGraph<x_t, y_t>(df0);
	g0->Draw("AC");
	g0->SetLineColor(3);

	auto g_zero= std::make_shared<TGraph>();
	g_zero->SetPoint(0, 0, 0);
	g_zero->Draw("same*");
	int index_max = 1;
	TTimer* timer = new TTimer(100);
	RQ_signals(timer).Timeout([&]() {
		++index_max;
		auto df_signal = fill_vector1(index_max,
			[&](auto index) -> x_t { return index; },
			[&](auto index) -> y_t { return 0.3 * TMath::Sin(index* Signal_frequency) + 1; }

		);

		c1->cd(1);
		auto g_signal = to_TGraph<x_t, y_t>(df_signal);
		g_signal->Draw("AC");
		c1->Modified();
		c1->Update();

		auto df1 = fill_vector1(index_max,
			[&](auto index) -> x_t { return y_t(df_signal[index]) * TMath::Cos(index * circle_frequency); },
			[&](auto index) -> y_t { return y_t(df_signal[index]) * TMath::Sin(index * circle_frequency); }

		);
		auto x_mean = mean<x_t>(df1);
		auto y_mean = mean<y_t>(df1);

		auto g_mean = std::make_shared<TGraph>();
		g_mean->SetPoint(0, x_mean, y_mean);
		g_mean_tail->SetPoint(g_mean_tail->GetN(), x_mean, y_mean);
		auto g = to_TGraph<x_t, y_t>(df1);
		c1->cd(2);
		g0->Draw("AC");
		g->Draw("same*");
		g_mean->Draw("same*");
		g_mean->SetMarkerColor(2);
		g_mean_tail->Draw("sameC");
		g_mean_tail->SetLineColor(46);
		g_zero->Draw("same*");
		g_zero->SetMarkerColor(4);

		c1->Modified();
		c1->Update();
	});
	timer->TurnOn();
	app.Run();

}
void ex03(int argc, char** argv) {
	TApplication app("myApp", &argc, argv);


	const double Signal_frequency = 0.2;
	double circle_frequency = 0;

	
	auto df_signal = fill_vector1(1000,
		[&](auto index) -> x_t { return index; },
		[&](auto index) -> y_t { return 0.3 * TMath::Sin(2 * TMath::Pi() * index * Signal_frequency) + 1; }

	);


	auto df0 = fill_vector1(100,
		[&](auto index) -> x_t { return TMath::Cos(index / 10.0); },
		[&](auto index) -> y_t { return TMath::Sin(index / 10.0); }

	);

	auto g_mean_tail = std::make_shared<TGraph>();

	auto c1 = new TCanvas();

	c1->Divide(2, 1);
	c1->cd(2);
	auto g0 = to_TGraph<x_t, y_t>(df0);
	g0->Draw("AC");
	g0->SetLineColor(3);

	auto g_zero = std::make_shared<TGraph>();
	g_zero->SetPoint(0, 0, 0);
	g_zero->Draw("same*");
	std::vector<std::tuple<frequency_t, x_t, y_t>> f_trans;
	TTimer* timer = new TTimer(100);
	RQ_signals(timer).Timeout([&]() {
	



		auto df1 = fill_vector1(df_signal.size(),
			[&](auto index) -> x_t { return y_t(df_signal[index]) * TMath::Cos(2 * TMath::Pi() * index * circle_frequency); },
			[&](auto index) -> y_t { return y_t(df_signal[index]) * TMath::Sin(2 * TMath::Pi() * index * circle_frequency); }

		);
		auto x_mean = mean<x_t>(df1);
		auto y_mean = mean<y_t>(df1);
		f_trans.emplace_back(circle_frequency, x_mean, y_mean);
		auto g_mean = std::make_shared<TGraph>();
		g_mean->SetPoint(0, x_mean, y_mean);
		g_mean_tail->SetPoint(g_mean_tail->GetN(), x_mean, y_mean);
		auto g = to_TGraph<x_t, y_t>(df1);
		c1->cd(2);
		g0->Draw("AC");
		g->Draw("same*");
		g_mean->Draw("same*");
		g_mean->SetMarkerColor(2);
		g_mean_tail->Draw("sameC");
		g_mean_tail->SetLineColor(46);
		g_zero->Draw("same*");
		g_zero->SetMarkerColor(4);


		c1->cd(1);
		auto g_f_x = to_TGraph<frequency_t, x_t>(f_trans);
		auto g_f_y = to_TGraph<frequency_t, y_t>(f_trans);
		
		g_f_x->Draw("AL");
		g_f_y->Draw("sameL");
		g_f_x->SetLineColor(2);
		g_f_y->SetLineColor(8);
		c1->Modified();
		c1->Update();


		circle_frequency += 0.0001;
	});
	timer->TurnOn();
	app.Run();

}
int main(int argc, char** argv) {


	

	ex03(argc, argv);

}