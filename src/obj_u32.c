#include "universe.h"

obj_u32_t* obj_u32_new(uint32_t value) {
    obj_u32_t* self = (obj_u32_t*) malloc(sizeof(obj_u32_t));
    obj_init((obj_t*) self, OBJ_TYPE_U32);
    self->value = value;
    return self;
}

void obj_u32_delete(obj_u32_t* self) {
    free(self);
}

bool is_u32(const obj_t* self) {
    return self->type == OBJ_TYPE_U32;
}

obj_ffi_t* obj_u32_to_ffi(const obj_u32_t* self) {
    assert(0 && "todo: implement");
}

void obj_u32_to_string(const obj_u32_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %u>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_u32_t* obj_u32_copy(const obj_u32_t* self) {
    obj_u32_t* copy = obj_u32_new(self->value);
    return copy;
}

bool obj_u32_equal(const obj_u32_t* self, const obj_u32_t* other) {
    return self->value == other->value;
}

bool obj_u32_is_truthy(const obj_u32_t* self) {
    return self->value != 0;
}

size_t obj_u32_hash(const obj_u32_t* self) {
    return (size_t) self->value;
}

obj_t* obj_u32_eval(const obj_u32_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_u32_apply(const obj_u32_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
