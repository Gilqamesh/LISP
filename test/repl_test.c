#include "repl_test.h"
#include "repl.h"

void repl_test() {
    repl_t repl;
    repl_init(&repl);

    printf("Starting REPL...\n");
    repl_run(&repl);
    printf("REPL terminated.\n");

    repl_destroy(&repl);
}
