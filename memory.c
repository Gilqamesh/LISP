#include "memory.h"

void memory_init(memory_t* memory) {
    memset(memory, 0, sizeof(memory_t));

    memory->total_allocated = 0;

    memory->obj_eof = (obj_eof_t*)malloc(sizeof(obj_eof_t));
    memory->total_allocated += sizeof(obj_eof_t);
    obj_eof_init(memory->obj_eof);

    memory->obj_nil = (obj_nil_t*)malloc(sizeof(obj_nil_t));
    memory->total_allocated += sizeof(obj_nil_t);
    obj_nil_init(memory->obj_nil);

    memory->obj_void = (obj_void_t*)malloc(sizeof(obj_void_t));
    memory->total_allocated += sizeof(obj_void_t);
    obj_void_init(memory->obj_void);
}

void memory_destroy(memory_t* memory) {
}

size_t memory_total_allocated(memory_t* memory) {
    return memory->total_allocated;
}

obj_t* memory_eof(memory_t* memory) {
    return (obj_t*) memory->obj_eof;
}

obj_t* memory_nil(memory_t* memory) {
    return (obj_t*) memory->obj_nil;
}

obj_t* memory_void(memory_t* memory) {
    return (obj_t*) memory->obj_void;
}

obj_t* memory_cons(memory_t* memory, obj_t* car, obj_t* cdr) {
    obj_cons_t* obj_cons = (obj_cons_t*)malloc(sizeof(obj_cons_t));
    memory->total_allocated += sizeof(obj_cons_t);
    obj_cons_init(obj_cons, car, cdr);
    return (obj_t*) obj_cons;
}

obj_t* memory_real(memory_t* memory, double real) {
    obj_real_t* obj_real = (obj_real_t*)malloc(sizeof(obj_real_t));
    memory->total_allocated += sizeof(obj_real_t);
    obj_real_init(obj_real, real);
    return (obj_t*) obj_real;
}

obj_t* memory_symbol(memory_t* memory, str_t symbol) {
    obj_symbol_t* obj_symbol = (obj_symbol_t*)malloc(sizeof(obj_symbol_t));
    memory->total_allocated += sizeof(obj_symbol_t);
    obj_symbol_init(obj_symbol, symbol);
    return (obj_t*) obj_symbol;
}

obj_t* memory_string(memory_t* memory, str_t string) {
    obj_string_t* obj_string = (obj_string_t*)malloc(sizeof(obj_string_t));
    memory->total_allocated += sizeof(obj_string_t);
    obj_string_init(obj_string, string);
    return (obj_t*) obj_string;
}

obj_t* memory_primitive(memory_t* memory, str_t name, primitive_t primitive) {
    obj_primitive_t* obj_primitive = (obj_primitive_t*)malloc(sizeof(obj_primitive_t));
    memory->total_allocated += sizeof(obj_primitive_t);
    obj_primitive_init(obj_primitive, name, primitive);
    return (obj_t*) obj_primitive;
}

obj_t* memory_macro(memory_t* memory, str_t name, macro_t macro) {
    obj_macro_t* obj_macro = (obj_macro_t*)malloc(sizeof(obj_macro_t));
    memory->total_allocated += sizeof(obj_macro_t);
    obj_macro_init(obj_macro, name, macro);
    return (obj_t*) obj_macro;
}

obj_t* memory_file(memory_t* memory, FILE* file) {
    obj_file_t* obj_file = (obj_file_t*)malloc(sizeof(obj_file_t));
    memory->total_allocated += sizeof(obj_file_t);
    obj_file_init(obj_file, file);
    return (obj_t*) obj_file;
}
