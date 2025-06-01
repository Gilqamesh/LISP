#include "universe.h"

obj_u16_t* obj_u16_new() {
    obj_u16_t* self = (obj_u16_t*) malloc(sizeof(obj_u16_t));
    obj_init((obj_t*) self, OBJ_TYPE_U16);
    assert(0 && "todo: implement");
    return self;
}

void obj_u16_delete(obj_u16_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_u16(const obj_t* self) {
    return self->type == OBJ_TYPE_U16;
}

obj_ffi_t* obj_u16_to_ffi(const obj_u16_t* self) {
    assert(0 && "todo: implement");
}

void obj_u16_to_string(const obj_u16_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(other, ">");
}

obj_u16_t* obj_u16_copy(const obj_u16_t* self) {
    obj_u16_t* copy = obj_u16_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_u16_equal(const obj_u16_t* self, const obj_u16_t* other) {
    assert(0 && "todo: implement");
}

bool obj_u16_is_truthy(const obj_u16_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_u16_hash(const obj_u16_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_u16_eval(const obj_u16_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_u16_apply(const obj_u16_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
