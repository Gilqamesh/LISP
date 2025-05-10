#ifndef REPL_H
# define REPL_H

# include "memory.h"
# include "reader.h"

typedef struct repl_t {
    memory_t memory;
    reader_t reader;
    obj_t* env;
} repl_t;

void repl_init(repl_t* self);
void repl_destroy(repl_t* self);

void repl_run(repl_t* self);

#endif // REPL_H
