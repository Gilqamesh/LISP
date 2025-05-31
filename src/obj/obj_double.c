#include "universe.h"

obj_double_t* obj_double_new() {
    obj_double_t* self = (obj_double_t*) malloc(sizeof(obj_double_t));
    obj_init((obj_t*) self, OBJ_TYPE_DOUBLE);
    assert(0 && "todo: implement");
    return self;
}

void obj_double_delete(obj_double_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_double(const obj_t* self) {
    return self->type == OBJ_TYPE_DOUBLE;
}

obj_ffi_t* obj_double_to_ffi(const obj_double_t* self) {
    assert(0 && "todo: implement");
}

void obj_double_to_string(const obj_double_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<double ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_double_copy(const obj_double_t* self) {
    obj_double_t* copy = obj_double_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_double_equal(const obj_double_t* self, const obj_double_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_double_hash(const obj_double_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_double_eval(const obj_double_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_double_apply(const obj_double_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
