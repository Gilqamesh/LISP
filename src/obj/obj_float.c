#include "universe.h"

obj_float_t* obj_float_new() {
    obj_float_t* self = (obj_float_t*) malloc(sizeof(obj_float_t));
    obj_init((obj_t*) self, OBJ_TYPE_FLOAT);
    assert(0 && "todo: implement");
    return self;
}

void obj_float_delete(obj_float_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_float(const obj_t* self) {
    return self->type == OBJ_TYPE_FLOAT;
}

obj_ffi_t* obj_float_to_ffi(const obj_float_t* self) {
    assert(0 && "todo: implement");
}

void obj_float_to_string(const obj_float_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<float ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_float_t* obj_float_copy(const obj_float_t* self) {
    obj_float_t* copy = obj_float_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_float_equal(const obj_float_t* self, const obj_float_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_float_hash(const obj_float_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_float_eval(const obj_float_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_float_apply(const obj_float_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
