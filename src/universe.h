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

    obj_t* obj_lisp_type_type;
    obj_t* obj_error_type;
    obj_t* obj_eof_type;
    obj_t* obj_nil_type;
    obj_t* obj_void_type;
    obj_t* obj_pointer_type;
    obj_t* obj_bool_type;
    obj_t* obj_cons_type;
    obj_t* obj_real_type;
    obj_t* obj_symbol_type;
    obj_t* obj_string_type;
    obj_t* obj_file_type;
    obj_t* obj_env_type;
    obj_t* obj_ffi_type;
    obj_t* obj_macro_type;
    obj_t* obj_function_primitive_type;
    obj_t* obj_function_compound_type;

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
