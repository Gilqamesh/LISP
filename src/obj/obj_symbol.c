#include "universe.h"

obj_symbol_t* obj_symbol_new() {
    obj_symbol_t* self = (obj_symbol_t*) malloc(sizeof(obj_symbol_t));
    obj_init((obj_t*) self, OBJ_TYPE_SYMBOL);
    assert(0 && "todo: implement");
    return self;
}

void obj_symbol_delete(obj_symbol_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_symbol(const obj_t* self) {
    return self->type == OBJ_TYPE_SYMBOL;
}

obj_ffi_t* obj_symbol_to_ffi(const obj_symbol_t* self) {
    assert(0 && "todo: implement");
}

void obj_symbol_to_string(const obj_symbol_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<symbol ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_symbol_copy(const obj_symbol_t* self) {
    obj_symbol_t* copy = obj_symbol_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_symbol_equal(const obj_symbol_t* self, const obj_symbol_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_symbol_hash(const obj_symbol_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_symbol_eval(const obj_symbol_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_symbol_apply(const obj_symbol_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
