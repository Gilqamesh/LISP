#ifndef UNIVERSE_H
# define UNIVERSE_H

# include "memory.h"
# include "obj.h"
# include "hasher.h"

typedef struct interned_entry_t {
    str_t s;
    obj_t* obj;
    size_t index;
} interned_entry_t;

typedef obj_t* (*reader_function_t)(FILE* file);

typedef struct reader_node_t {
    struct reader_node_t* children[128];
    reader_function_t reader_function;
} reader_node_t;

typedef struct universe_t {
    reader_node_t reader_node;
    obj_t* env;

    size_t total_allocated;

    obj_t* obj_types[_OBJ_TYPE_SIZE];

    obj_t* obj_eof;
    obj_t* obj_nil;
    obj_t* obj_void;
    obj_t* obj_true;
    obj_t* obj_false;

    size_t interned_entries_size;
    size_t interned_entries_top;
    interned_entry_t** interned_entries;
    hasher_t interned_symbols;

    void* dlhandle;
} universe_t;

bool universe_init();
void universe_destroy();

void universe_run();

#endif // UNIVERSE_H
