#include "timer.hpp"
#include "manyakSDL.hpp"

Timer::Timer() {
    mTime = SDL_GetTicks();
}

float Timer::getElapsedSeconds() {
    unsigned int newTime = SDL_GetTicks();
    unsigned int elapsed = newTime - mTime;
    mTime = newTime;
    return (float)elapsed / 1000.f;
}