#include "universe.h"

obj_symbol_t* obj_symbol_new(obj_string_t* symbol) {
    obj_symbol_t* self = (obj_symbol_t*) malloc(sizeof(obj_symbol_t));
    obj_init((obj_t*) self, OBJ_TYPE_SYMBOL);
    self->symbol = symbol;
    return self;
}

void obj_symbol_delete(obj_symbol_t* self) {
    if (self->symbol) {
        obj_string_delete(self->symbol);
    }
    free(self);
}

bool is_symbol(const obj_t* self) {
    return self->type == OBJ_TYPE_SYMBOL;
}

obj_ffi_t* obj_symbol_to_ffi(const obj_symbol_t* self) {
    assert(0 && "todo: implement");
}

void obj_symbol_to_string(const obj_symbol_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<symbol ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_string(str, self->symbol);
    obj_string_push_cstr(str, ">");
}

obj_symbol_t* obj_symbol_copy(const obj_symbol_t* self) {
    obj_symbol_t* copy = obj_symbol_new(obj_string_copy(self->symbol));
    return copy;
}

bool obj_symbol_equal(const obj_symbol_t* self, const obj_symbol_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_symbol_hash(const obj_symbol_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_symbol_eval(const obj_symbol_t* self, obj_env_t* env) {
    return obj_env_get(env, (obj_t*) self->symbol);
}

obj_t* obj_symbol_apply(const obj_symbol_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
