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