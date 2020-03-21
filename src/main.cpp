#include <iostream>
#include <SDL2/SDL.h>

#include "environment.hpp"

int main(int argc, const char *argv[]) {
    Environment env;
    env.initialize();
    env.start();
}