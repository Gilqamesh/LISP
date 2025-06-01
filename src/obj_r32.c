#include "universe.h"

obj_r32_t* obj_r32_new(float value) {
    obj_r32_t* self = (obj_r32_t*) malloc(sizeof(obj_r32_t));
    obj_init((obj_t*) self, OBJ_TYPE_R32);
    self->value = value;
    return self;
}

void obj_r32_delete(obj_r32_t* self) {
    free(self);
}

bool is_r32(const obj_t* self) {
    return self->type == OBJ_TYPE_R32;
}

obj_ffi_t* obj_r32_to_ffi(const obj_r32_t* self) {
    assert(0 && "todo: implement");
}

void obj_r32_to_string(const obj_r32_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %f>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_r32_t* obj_r32_copy(const obj_r32_t* self) {
    obj_r32_t* copy = obj_r32_new(self->value);
    return copy;
}

bool obj_r32_equal(const obj_r32_t* self, const obj_r32_t* other) {
    return self->value == other->value;
}

bool obj_r32_is_truthy(const obj_r32_t* self) {
    return self->value != 0.0f;
}

size_t obj_r32_hash(const obj_r32_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_r32_eval(const obj_r32_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_r32_apply(const obj_r32_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
