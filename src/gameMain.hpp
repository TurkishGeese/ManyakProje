#pragma once

#include "platform.hpp"
#include "environment.hpp"

typedef Environment*(*getEnvironmentFunction)();

extern "C" EXPORT Environment* getEnvironment();

typedef bool(*startGameFunction)(Environment *environment);

extern "C" EXPORT bool startGame(Environment *environment);
