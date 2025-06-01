#include "universe.h"

obj_ffi_t* obj_ffi_new() {
    obj_ffi_t* self = (obj_ffi_t*) malloc(sizeof(obj_ffi_t));
    obj_init((obj_t*) self, OBJ_TYPE_FFI);
    assert(0 && "todo: implement");
    return self;
}

void obj_ffi_delete(obj_ffi_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_ffi(const obj_t* self) {
    return self->type == OBJ_TYPE_FFI;
}

obj_ffi_t* obj_ffi_to_ffi(const obj_ffi_t* self) {
    return (obj_ffi_t*) self;
}

void obj_ffi_to_string(const obj_ffi_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_ffi_t* obj_ffi_copy(const obj_ffi_t* self) {
    obj_ffi_t* copy = obj_ffi_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_ffi_equal(const obj_ffi_t* self, const obj_ffi_t* other) {
    assert(0 && "todo: implement");
}

bool obj_ffi_is_truthy(const obj_ffi_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_ffi_hash(const obj_ffi_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_ffi_eval(const obj_ffi_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_ffi_apply(const obj_ffi_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
