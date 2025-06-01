#include "universe.h"

obj_i8_t* obj_i8_new(int8_t value) {
    obj_i8_t* self = (obj_i8_t*) malloc(sizeof(obj_i8_t));
    obj_init((obj_t*) self, OBJ_TYPE_I8);
    self->value = value;
    return self;
}

void obj_i8_delete(obj_i8_t* self) {
    free(self);
}

bool is_i8(const obj_t* self) {
    return self->type == OBJ_TYPE_I8;
}

obj_ffi_t* obj_i8_to_ffi(const obj_i8_t* self) {
    assert(0 && "todo: implement");
}

void obj_i8_to_string(const obj_i8_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %d>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_i8_t* obj_i8_copy(const obj_i8_t* self) {
    obj_i8_t* copy = obj_i8_new(self->value);
    return copy;
}

bool obj_i8_equal(const obj_i8_t* self, const obj_i8_t* other) {
    return self->value == other->value;
}

bool obj_i8_is_truthy(const obj_i8_t* self) {
    return self->value != 0;
}

size_t obj_i8_hash(const obj_i8_t* self) {
    return (size_t) self->value;
}

obj_t* obj_i8_eval(const obj_i8_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_i8_apply(const obj_i8_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
