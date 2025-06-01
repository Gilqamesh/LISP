#include "universe.h"

obj_i32_t* obj_i32_new(int32_t value) {
    obj_i32_t* self = (obj_i32_t*) malloc(sizeof(obj_i32_t));
    obj_init((obj_t*) self, OBJ_TYPE_I32);
    self->value = value;
    return self;
}

void obj_i32_delete(obj_i32_t* self) {
    free(self);
}

bool is_i32(const obj_t* self) {
    return self->type == OBJ_TYPE_I32;
}

obj_ffi_t* obj_i32_to_ffi(const obj_i32_t* self) {
    assert(0 && "todo: implement");
}

void obj_i32_to_string(const obj_i32_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %d>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_i32_t* obj_i32_copy(const obj_i32_t* self) {
    obj_i32_t* copy = obj_i32_new(self->value);
    return copy;
}

bool obj_i32_equal(const obj_i32_t* self, const obj_i32_t* other) {
    return self->value == other->value;
}

bool obj_i32_is_truthy(const obj_i32_t* self) {
    return self->value != 0;
}

size_t obj_i32_hash(const obj_i32_t* self) {
    return (size_t) self->value;
}

obj_t* obj_i32_eval(const obj_i32_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_i32_apply(const obj_i32_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
