#pragma  once


#include "TImage.h"
#include "TApplication.h"
#include <iostream>
#include "group_helper.hh"
#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TBrowser.h"
#include "TTimer.h"
#include "TGraph.h"
#include "TMarker.h"

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include "TMath.h"
#include <bitset>
#include <memory>
#include <optional>
#include <span>

namespace group_helper {
	namespace group_colors {
		enum color_t {
			White = 0,
			Black = 1,
			Gray = 920,
			Red = 632,
			Green = 416,
			Blue = 600,
			Yellow = 400,
			Magenta = 616,
			Cyan = 432,
			Orange = 800,
			Spring = 820,
			Teal = 840,
			Azure = 860,
			Violet = 880,
			Pink = 900
		};
	}
	template <typename XAxis_t, typename YAsis_t, typename VEC_t>
	std::shared_ptr<TGraph> to_TGraph(const VEC_t& vec) {
		auto ret = std::make_shared<TGraph>();

		for (const auto& e : vec) {
			ret->SetPoint(ret->GetN(), XAxis_t(e), YAsis_t(e));
		}
		return  ret;
	}

	template <typename XAxis_t, typename YAsis_t, typename VEC_t>
	std::shared_ptr<TGraph> plot(const VEC_t& vec, const char* options = "AC") {
		auto ret = to_TGraph< XAxis_t, YAsis_t>(vec);

		ret->Draw(options);
		return  ret;
	}


	template <typename XAxis_t, typename YAsis_t>
	std::shared_ptr<TGraph> plot(const XAxis_t& x, const YAsis_t& y, 
								 const char* options = "AC", 
								 group_colors::color_t mcolor = group_colors::Black) {

		auto ret = std::make_shared<TGraph>();
		auto x_itt = x.begin();
		auto y_itt = y.begin();
		while( x_itt != x.end() && y_itt != y.end()) {
			ret->SetPoint(ret->GetN(), *x_itt, *y_itt);
			++x_itt;
			++y_itt;
		}
		if (ret->GetN() == 0){
			return ret;
		}
		ret->Draw(options);
		ret->SetFillColor(mcolor);
		ret->SetLineColor(mcolor);
		ret->SetMarkerColor(mcolor);
		return  ret;
	}


	template <typename XAxis_t, typename YAsis_t, typename VEC_t>
	std::shared_ptr<TGraph> plot_with_tail(const VEC_t& vec, const char* options = "AC") {
		auto s_vec = std::span(vec);
		auto ret = to_TGraph< XAxis_t, YAsis_t>(s_vec.subspan(std::max(0, (int)s_vec.size() - 50)));

		ret->Draw(options);
		return  ret;
	}

	template <typename XAxis_t, typename YAsis_t, typename Color_T, typename VEC_t>
	auto plot_color(const VEC_t& vec, const char* options = "") {
		std::vector<std::shared_ptr<TMarker>> ret;
		for (const auto& e : vec) {
			TMarker* m = new TMarker(XAxis_t(e), YAsis_t(e), 20);
			m->SetMarkerSize(1);
			m->SetMarkerColor(31 + Color_T(e));
			m->Draw();
			ret.emplace_back(m);
		}

		return  ret;
	}
}