#include "universe.h"

obj_t* obj_symbol_new(obj_t* symbol) {
    obj_symbol_t* self = (obj_symbol_t*) malloc(sizeof(obj_symbol_t));
    obj_init((obj_t*) self, OBJ_TYPE_SYMBOL);
    self->symbol = symbol;
    return (obj_t*) self;
}

void obj_symbol_delete(obj_t* self) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    if (obj_symbol->symbol) {
        obj_string_delete(obj_symbol->symbol);
    }
    free(self);
}

bool is_symbol(obj_t* self) {
    return self->type == OBJ_TYPE_SYMBOL;
}

obj_symbol_t* obj_as_symbol(obj_t* self) {
    if (!is_symbol(self)) {
        throw(obj_string_new_cstr("expected obj_symbol_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_symbol_t*) self;
}

ffi_type* obj_symbol_to_ffi(obj_t* self) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    assert(0 && "todo: implement");
}

void obj_symbol_to_string(obj_t* self, obj_t* string) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_string_push_string(string, obj_symbol->symbol);
    obj_string_push_cstr(string, ">");
}

obj_t* obj_symbol_copy(obj_t* self) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    obj_t* copy = obj_symbol_new(obj_string_copy(obj_symbol->symbol));
    return copy;
}

bool obj_symbol_is_equal(obj_t* self, obj_t* other) {
    obj_symbol_t* obj_symbol_self = obj_as_symbol(self);
    obj_symbol_t* obj_symbol_other = obj_as_symbol(other);
    return obj_string_is_equal(obj_symbol_self->symbol, obj_symbol_other->symbol);
}

bool obj_symbol_is_truthy(obj_t* self) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    assert(0 && "todo: implement");
}

size_t obj_symbol_hash(obj_t* self) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    return obj_string_hash(obj_symbol->symbol);
}

obj_t* obj_symbol_eval(obj_t* self, obj_t* env) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    return obj_env_get(env, self);
}

obj_t* obj_symbol_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_symbol_t* obj_symbol = obj_as_symbol(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
