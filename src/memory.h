#ifndef MEMORY_H
# define MEMORY_H

# include "libc.h"
# include "obj.h"
# include "hasher.h"

typedef struct interned_entry_t {
    str_t s;
    obj_t* obj;
    size_t index;
} interned_entry_t;

typedef struct memory_t {
    size_t total_allocated;

    obj_eof_t* obj_eof;
    obj_nil_t* obj_nil;
    obj_void_t* obj_void;
    obj_bool_t* obj_true;
    obj_bool_t* obj_false;

    size_t interned_entries_size;
    size_t interned_entries_top;
    interned_entry_t** interned_entries;

    hasher_t interned_symbols;
} memory_t;

void memory_init(memory_t* self);
void memory_destroy(memory_t* self);

size_t memory_total_allocated(memory_t* self);

obj_t* memory_error(memory_t* self, str_t message);
obj_t* memory_eof(memory_t* self);
obj_t* memory_nil(memory_t* self);
obj_t* memory_void(memory_t* self);
obj_t* memory_bool(memory_t* self, bool boolean);
obj_t* memory_cons(memory_t* self, obj_t* car, obj_t* cdr);
obj_t* memory_real(memory_t* self, double real);
obj_t* memory_symbol(memory_t* self, str_t symbol);
obj_t* memory_string(memory_t* self, str_t string);
obj_t* memory_file(memory_t* self, FILE* file);
obj_t* memory_env(memory_t* self);
obj_t* get_env_binding(memory_t* memory, obj_t* obj, obj_t* key);
obj_t* set_env_binding(memory_t* memory, obj_t* obj, obj_t* key, obj_t* value);
obj_t* define_env_binding(memory_t* memory, obj_t* obj, obj_t* key, obj_t* value);

obj_t* memory_macro(memory_t* self, obj_t* params, obj_t* body);

obj_t* memory_primitive(memory_t* self, str_t name, primitive_t primitive);
obj_t* memory_compound(memory_t* self, obj_t* params, obj_t* body, obj_t* env);

#endif // MEMORY_H
