#pragma once
#include "pch.h"


class MyColor {

	int red, green, blue;

public:

	MyColor(long int bigInt) {
		red = bigInt / (1000000);
		green = (bigInt-red) / 1000;
		blue = bigInt - (red + green);
	}

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

