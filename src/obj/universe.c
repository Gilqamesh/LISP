#include "universe.h"

universe_t UNIVERSE;

void universe_init(int argc, char** argv) {
    UNIVERSE.argc = argc;
    UNIVERSE.argv = argv;
}

void universe_deinit(void) {
}
