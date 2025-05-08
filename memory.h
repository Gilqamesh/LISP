#ifndef MEMORY_H
# define MEMORY_H

# include "libc.h"
# include "obj.h"

typedef struct memory_t {
    size_t total_allocated;

    obj_eof_t* obj_eof;
    obj_nil_t* obj_nil;
    obj_void_t* obj_void;
} memory_t;

void memory_init(memory_t* memory);
void memory_destroy(memory_t* memory);

size_t memory_total_allocated(memory_t* memory);

obj_t* memory_eof(memory_t* memory);
obj_t* memory_nil(memory_t* memory);
obj_t* memory_void(memory_t* memory);
obj_t* memory_cons(memory_t* memory, obj_t* car, obj_t* cdr);
obj_t* memory_real(memory_t* memory, double real);
obj_t* memory_symbol(memory_t* memory, str_t symbol);
obj_t* memory_string(memory_t* memory, str_t string);
obj_t* memory_primitive(memory_t* memory, str_t name, primitive_t primitive);
obj_t* memory_macro(memory_t* memory, str_t name, macro_t macro);
obj_t* memory_file(memory_t* memory, FILE* file);

#endif // MEMORY_H
