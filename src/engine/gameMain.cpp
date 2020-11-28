#include "gameMain.hpp"
#include "manyakSDL.hpp"
#include "environment.hpp"


Environment* getEnvironment() {
	return new Environment();
}

bool startGame(Environment* environment) {
	environment->initialize();
	return environment->start();
}