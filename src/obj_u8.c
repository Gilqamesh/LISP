#include "universe.h"

obj_u8_t* obj_u8_new(uint8_t value) {
    obj_u8_t* self = (obj_u8_t*) malloc(sizeof(obj_u8_t));
    obj_init((obj_t*) self, OBJ_TYPE_U8);
    self->value = value;
    return self;
}

void obj_u8_delete(obj_u8_t* self) {
    free(self);
}

bool is_u8(const obj_t* self) {
    return self->type == OBJ_TYPE_U8;
}

obj_ffi_t* obj_u8_to_ffi(const obj_u8_t* self) {
    assert(0 && "todo: implement");
}

void obj_u8_to_string(const obj_u8_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %u>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_u8_t* obj_u8_copy(const obj_u8_t* self) {
    obj_u8_t* copy = obj_u8_new(self->value);
    return copy;
}

bool obj_u8_equal(const obj_u8_t* self, const obj_u8_t* other) {
    return self->value == other->value;
}

bool obj_u8_is_truthy(const obj_u8_t* self) {
    return self->value != 0;
}

size_t obj_u8_hash(const obj_u8_t* self) {
    return (size_t) self->value;
}

obj_t* obj_u8_eval(const obj_u8_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_u8_apply(const obj_u8_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
