#include "universe_test.h"
#include "universe.h"

void universe_test() {
    if (!universe_init()) {
        assert(0);
    }

    printf("Starting universe...\n");
    universe_run();
    printf("Universe terminated.\n");

    universe_destroy();
}
