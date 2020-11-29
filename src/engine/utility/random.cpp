#include "random.hpp"
#include <ctime>

int Random::getRandomNumberBetween(int i, int j) {
	if (sInstance == nullptr)
		sInstance = new Random();
	return sInstance->internalGetRandomNumberBetween(i, j);
}

Random::Random() {
	mRng.seed((unsigned)time(0));
}

int Random::internalGetRandomNumberBetween(int i, int j) {
	std::uniform_int_distribution<int> dist(i, j);
	return dist(mRng);
}