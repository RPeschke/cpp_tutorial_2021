#pragma  once


namespace group_helper {
	template<class T>
	concept range_container_t = requires(const T & t) {
		t.begin();
		t.end();
	};

}