#include "universe.h"

universe_t UNIVERSE;

void universe_init(int argc, char** argv) {
    UNIVERSE.argc = argc;
    UNIVERSE.argv = argv;
    UNIVERSE.backtrace_state = backtrace_create_state(argv[0], 0, NULL, NULL);
}

void universe_deinit(void) {
}
