#pragma once

#include <random>

class Random {

public:
	static int getRandomNumberBetween(int i, int j);

private:
	inline static Random* sInstance = nullptr;

	Random();
	int internalGetRandomNumberBetween(int i, int j);

	std::mt19937 mRng;
};