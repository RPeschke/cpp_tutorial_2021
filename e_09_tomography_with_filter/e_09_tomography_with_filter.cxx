
#include <iostream>
#include <fstream>
#include "group_helper.hh"
#include "TImage.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TApplication.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TBrowser.h"
#include "TTimer.h"
#include "TGSignals.hh"
#include < utility >
#include  <type_traits>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/all.hpp>


using namespace group_helper;

AXIS_NAME(index_t, int);
AXIS_NAME(height, int);
AXIS_NAME(Width, int);
AXIS_NAME(Color, int);
AXIS_NAME(Color_d, double);
AXIS_NAME(Filter_t, double);

AXIS_NAME(angle, double);
AXIS_NAME(x_axis, int);
AXIS_NAME(projection, double);

AXIS_NAME(height_frequency, double);
AXIS_NAME(Width_frequency, double);
AXIS_NAME(Intensity_real, double);
AXIS_NAME(Intensity_img, double);



using img_vect_e = std::tuple< height, Width, Color>;
using img_vect_t = std::vector<img_vect_e>;

using img_fourier_e = std::tuple< height_frequency, Width_frequency, Intensity_real, Intensity_img>;
using img_fourier_t = std::vector<img_fourier_e>;

using sinogram_e = std::tuple<angle, x_axis, projection>;
using sinogram_t = std::vector<sinogram_e >;

using img_vect_rec_e = std::tuple<height, Width, Color_d>;
using img_vect_rec_t = std::vector<img_vect_rec_e >;

template <typename T1, typename T>
T1 get_element(T& vec, size_t i) {
	if (i < 0) {
		return T1{};
	}
	if (i >= vec.size()) {
		return T1{};
	}
	return  T1(vec[i]);
}



template <int N, typename T>
auto add_branch(TTree* tree, T& element) {
	auto branchName = __get__name__(std::get<N>(element));

	tree->Branch(branchName.c_str(), &std::get<N>(element), __get__name__and_type(std::get<N>(element)).c_str());
	if constexpr (N > 0) {
		add_branch<N - 1>(tree, element);
	}
}

template <typename T>
void save(const std::string& FileName, const std::vector<T>& vec, const std::string& BranchName, const std::string& FileNode = "RECREATE") {
	TFile* f = new TFile(FileName.c_str(), FileNode.c_str());

	TTree* tree = new TTree(BranchName.c_str(), BranchName.c_str());
	T element{};

	add_branch<std::tuple_size_v<T> -1 >(tree, element);
	for (const auto& e : vec) {
		element = e;
		tree->Fill();
	}

	tree->Write();
	f->Write();
	delete f;
}



std::vector<double> get_filter_core(double a) {
	std::vector<double> ret;
	for (auto e1 : ranges::view::ints(-8, 8)) {
		double e = e1 + 0.001;
		double v = a * TMath::Sin(2 * TMath::Pi() * e * a) / (TMath::Pi() * e)
			+ TMath::Power(TMath::Sin(2 * TMath::Pi() * e * a) / (TMath::Pi() * e), 2);
		ret.push_back(v);
	}

	return ret;
}

std::vector<double> get_filter_core() {


	return { -1.0 / (TMath::Pi() * TMath::Pi()) , 1.0 / 4, -1.0 / (TMath::Pi() * TMath::Pi()) };
}

img_vect_t image2vector(TImage* img) {
	auto argb = img->GetArgbArray();
	int h = img->GetHeight();
	int w = img->GetWidth();
	int height0 = h / 2, Width0 = w / 2;
	return fill_vector1(h * w,
		[&](auto index) -> height { return index / w - height0; },
		[&](auto index) -> Width { return index % (w)-Width0; },
		[&](auto index) -> Color {
		return
			(((argb[index] & 0xff0000) >> 16) +
				((argb[index] & 0xff00) >> 8) +
				(argb[index] & 0xff));
	}
	);
}

sinogram_t imgVector2Projection(const img_vect_t& imVec, double angle_radiand) {
	auto df_projection = fill_vector(imVec,
		[&](const auto& e) -> angle { return angle_radiand; },
		[&](const auto& e) -> x_axis { return (height(e)) * TMath::Cos(angle_radiand) - (Width(e)) * TMath::Sin(angle_radiand); },
		[&](const auto& e) -> projection { return (int)Color(e); }
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
	return df_summed_projection;
}


sinogram_t imgVector2Sinogram(const img_vect_t& imVec) {
	sinogram_t df_summed;
	for (double angle_ = 0; angle_ < 180; angle_ += 1) {
		const auto df_summed_projection = imgVector2Projection(imVec, TMath::DegToRad() * angle_);
		df_summed.insert(std::end(df_summed), std::begin(df_summed_projection), std::end(df_summed_projection));
	}
	std::sort(df_summed.begin(), df_summed.end());
	return df_summed;
}



img_vect_rec_t reconstruct(const sinogram_t& df_sinograph, int grid) {
	auto df_grouped = group_helper::group<angle>::get(df_sinograph);



	auto df_reconstructed = fill_vector1(grid * grid * 4,
		[&](auto index) -> height { return index / (2 * grid) - grid; },
		[&](auto index) -> Width { return index % (2 * grid) - grid; },
		[&](auto index) -> Color_d {
		const int i = index / (2 * grid) - grid;
		const int j = index % (2 * grid) - grid;
		double ret = 0;
		for (const auto& current_angle : df_grouped) {
			auto df = std::get<1>(current_angle);
			const double angle1 = angle(current_angle);
			double tx = TMath::Cos(angle1);
			double ty = -TMath::Sin(angle1);
			int lamda = i * tx + j * ty;

			auto x23 = x_axis(df[0]);
			ret += get_element<projection>(df, lamda - x23);
		}
		return ret;

	}
	);

	return df_reconstructed;

}

auto apply_filter(const sinogram_t& df_sinogram, std::vector<double> FilterCore) {


	auto df_filtered = group_helper::group<angle>::apply1(df_sinogram,
		[&](const auto& e) {
		const auto filterCore = FilterCore;// get_filter_core();
		std::vector< std::tuple< x_axis, projection> > ret;
		for (int i = 0; i < e.size(); ++i) {
			double dummy = 0;
			for (size_t j = 0; j < e.size(); ++j) {
				dummy += get_element< projection>(e, j) * get_element<double>(filterCore, i - j);
			}
			ret.emplace_back(get_element<x_axis>(e, i), dummy);
		}


		return ret;
	}
	);

	return df_filtered;
}

template <typename T,typename T1, typename T2>
bool element_not_containt_in_vector(const T1& element, const T2& vector_) {
	return std::find_if(vector_.begin(), vector_.end(), [&](const auto& e1) { return e1 == T(element);  }) == vector_.end();
}


template <typename T1, typename T2> 
auto fourier_2d(const T2& vec) {
	
	const auto [min_height, max_height, min_Width, max_Width] = [&]() {

		double max_height = -10000;
		double max_Width = -100000;
		double min_height = 100000;
		double min_Width = 100000;
		for (const auto& e : vec) {
			max_height = std::max((double)height(e), max_height);
			max_Width = std::max((double)Width(e), max_Width);
			min_height = std::min((double)height(e), min_height);
			min_Width = std::min((double)Width(e), min_Width);
		}
		return std::make_tuple(min_height, max_height, min_Width, max_Width);
	}();

	
	auto df_filtered = group_helper::group<height, Width>::apply(vec,
		[&](const auto& e) -> height_frequency { return (height(e[0])  - min_height) /( max_height - min_height) ; },
		[&](const auto& e) -> Width_frequency { return  (Width(e[0]) - min_Width)  / (max_Width - min_Width); },
		[&](const auto& e) -> Intensity_real {
			double ret_real = 0;
			const auto  e_height = (height(e[0]) - min_height) / (max_height - min_height);
			const auto  e_Width  = (Width(e[0]) - min_Width) / (max_Width - min_Width);
			for (const auto& e1 : vec) {
				ret_real += 1.0 * T1(e1) * TMath::Cos(-2.0 * TMath::Pi() * (height(e1) * e_height + Width(e1) * e_Width));
			}
			return  ret_real; 
		},
		[&](const auto& e)  -> Intensity_img {
			double ret_img = 0;
			const auto  e_height = (height(e[0]) - min_height) / (max_height - min_height);
			const auto  e_Width = (Width(e[0]) - min_Width) / (max_Width - min_Width);
			for (const auto& e1 : vec) {
				ret_img += 1.0 * T1(e1) * TMath::Sin(-2.0 * TMath::Pi() * (height(e1) * e_height + Width(e1) * e_Width));
			}
			return  ret_img; 
		}
	);

	return df_filtered;

}
//______________________________________________________________________________
int main(int argc, char** argv) {








	auto name_pro = __get__name__(projection());


	TImage* img = TImage::Open("../../e_07_tomography/threedots.jpg");
	const std::string oFileName = "test13.root";

	auto argb = img->GetArgbArray();

	auto df_img = image2vector(img);




	const auto df_summed = imgVector2Sinogram(df_img);
	
	const int i_max = TMath::Max(img->GetHeight(), img->GetWidth());

	const auto df_reconstructed = reconstruct(df_summed, i_max);



	const auto df_filtered = apply_filter(df_summed, get_filter_core());
	const auto df_reconstructed_filtered = reconstruct(df_filtered, i_max);




	save(oFileName, df_img, "df_img");
	save(oFileName, df_summed, "df_summed", "update");
	save(oFileName, df_reconstructed, "df_reconstructed", "update");
	save(oFileName, df_reconstructed_filtered, "df_reconstructed_filtered", "update");
	save(oFileName, df_filtered, "df_sinogram_filtered", "update");
	
	auto fourier_filtered = fourier_2d<Color_d>(df_reconstructed_filtered);
 	save(oFileName, fourier_filtered, "fourier_filtered", "update");
	auto fourier_original = fourier_2d<Color>(df_img);
	save(oFileName, fourier_original, "fourier_original", "update");
	auto fourier_reco = fourier_2d<Color_d>(df_reconstructed);
	save(oFileName, fourier_reco, "fourier_reco", "update");
}