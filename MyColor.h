#pragma once
#include <vector>


class MyColor {

	int red, green, blue;

public:

	MyColor(const std::vector<int>& arr) :
		red(arr[0]), green(arr[1]), blue(arr[2]) {}


	MyColor(int r = 0, int g = 0, int b = 0) :
		red(r), green(g), blue(b) {}


	int Red() const {
		return red;
	}

	int Green() const {
		return green;
	}

	int Blue() const {
		return blue;
	}
};

