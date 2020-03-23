#include "environment.hpp"

#if defined(MANYAK_MAC)
int main(int argc, const char* argv[]) {
    Environment env;
    env.initialize();
    env.start();
}
#elif defined(MANYAK_WIN32)
int wmain(int argc, const char* argv[]) {
    Environment env;
    env.initialize();
    env.start();
}
#endif