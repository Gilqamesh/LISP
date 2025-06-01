#include "universe.h"

obj_lisp_type_t* obj_lisp_type_new() {
    obj_lisp_type_t* self = (obj_lisp_type_t*) malloc(sizeof(obj_lisp_type_t));
    obj_init((obj_t*) self, OBJ_TYPE_LISP_TYPE);
    assert(0 && "todo: implement");
    return self;
}

void obj_lisp_type_delete(obj_lisp_type_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_lisp_type(const obj_t* self) {
    return self->type == OBJ_TYPE_LISP_TYPE;
}

obj_ffi_t* obj_lisp_type_to_ffi(const obj_lisp_type_t* self) {
    assert(0 && "todo: implement");
}

void obj_lisp_type_to_string(const obj_lisp_type_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_lisp_type_t* obj_lisp_type_copy(const obj_lisp_type_t* self) {
    obj_lisp_type_t* copy = obj_lisp_type_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_lisp_type_equal(const obj_lisp_type_t* self, const obj_lisp_type_t* other) {
    assert(0 && "todo: implement");
}

bool obj_lisp_type_is_truthy(const obj_lisp_type_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_lisp_type_hash(const obj_lisp_type_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_lisp_type_eval(const obj_lisp_type_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_lisp_type_apply(const obj_lisp_type_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
