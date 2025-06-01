#include "universe.h"

obj_r64_t* obj_r64_new(double value) {
    obj_r64_t* self = (obj_r64_t*) malloc(sizeof(obj_r64_t));
    obj_init((obj_t*) self, OBJ_TYPE_R64);
    self->value = value;
    return self;
}

void obj_r64_delete(obj_r64_t* self) {
    free(self);
}

bool is_r64(const obj_t* self) {
    return self->type == OBJ_TYPE_R64;
}

obj_ffi_t* obj_r64_to_ffi(const obj_r64_t* self) {
    assert(0 && "todo: implement");
}

void obj_r64_to_string(const obj_r64_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %lf>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_r64_t* obj_r64_copy(const obj_r64_t* self) {
    obj_r64_t* copy = obj_r64_new(self->value);
    return copy;
}

bool obj_r64_equal(const obj_r64_t* self, const obj_r64_t* other) {
    return self->value == other->value;
}

bool obj_r64_is_truthy(const obj_r64_t* self) {
    return self->value != 0.0;
}

size_t obj_r64_hash(const obj_r64_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_r64_eval(const obj_r64_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_r64_apply(const obj_r64_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
