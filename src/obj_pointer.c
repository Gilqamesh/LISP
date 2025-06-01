#include "universe.h"

obj_pointer_t* obj_pointer_new() {
    obj_pointer_t* self = (obj_pointer_t*) malloc(sizeof(obj_pointer_t));
    obj_init((obj_t*) self, OBJ_TYPE_POINTER);
    assert(0 && "todo: implement");
    return self;
}

void obj_pointer_delete(obj_pointer_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_pointer(const obj_t* self) {
    return self->type == OBJ_TYPE_POINTER;
}

obj_ffi_t* obj_pointer_to_ffi(const obj_pointer_t* self) {
    assert(0 && "todo: implement");
}

void obj_pointer_to_string(const obj_pointer_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_pointer_t* obj_pointer_copy(const obj_pointer_t* self) {
    obj_pointer_t* copy = obj_pointer_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_pointer_equal(const obj_pointer_t* self, const obj_pointer_t* other) {
    assert(0 && "todo: implement");
}

bool obj_pointer_is_truthy(const obj_pointer_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_pointer_hash(const obj_pointer_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_pointer_eval(const obj_pointer_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_pointer_apply(const obj_pointer_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
