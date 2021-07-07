#pragma  once

#include "TFile.h"
#include "TTree.h"




template <typename T>
void add_branch_element(TTree* tree, const std::string& prefix,  T& element) {
	auto branchName = prefix + __get__name__(element);

	tree->Branch(branchName.c_str(), &element, __get__name__and_type(element).c_str());

}


template <int N, typename T>
auto add_branch(TTree* tree, const std::string& prefix,  T& element) {
	add_branch_element(tree, prefix, std::get<N>(element));
	//auto branchName =  __get__name__(std::get<N>(element));

	//tree->Branch(branchName.c_str(), &std::get<N>(element), __get__name__and_type(std::get<N>(element)).c_str());
	if constexpr (N > 0) {
		add_branch<N - 1>(tree, prefix,element);
	}
}


template <int N, typename... T>
void add_branch(TTree* tree, const std::string& prefix, std::pair<T...>& element) {

	add_branch< std::tuple_size_v<decltype(element.first) > -1 >(tree, prefix+ "rhs_", element.first);
	add_branch< std::tuple_size_v<decltype(element.second)> -1 >(tree, prefix+ "lhs_", element.second);
	//auto branchName = prefix + __get__name__(element);

	//tree->Branch(branchName.c_str(), &element, __get__name__and_type(element).c_str());
	std::cout << "sada\n";

}

template <typename T>
void save(const std::string& FileName, const std::vector<T>& vec, const std::string& BranchName, const std::string& FileNode = "RECREATE") {
	TFile* f = new TFile(FileName.c_str(), FileNode.c_str());

	TTree* tree = new TTree(BranchName.c_str(), BranchName.c_str());
	T element{};

	add_branch<std::tuple_size_v<T> -1 >(tree, "", element);
	for (const auto& e : vec) {
		element = e;
		tree->Fill();
	}

	tree->Write();
	f->Write();
	delete f;
}

