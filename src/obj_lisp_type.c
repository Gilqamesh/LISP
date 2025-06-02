#include "universe.h"

obj_t* obj_lisp_type_new() {
    obj_lisp_type_t* self = (obj_lisp_type_t*) malloc(sizeof(obj_lisp_type_t));
    obj_init((obj_t*) self, OBJ_TYPE_LISP_TYPE);
    assert(0 && "todo: implement");
    return (obj_t*) self;
}

void obj_lisp_type_delete(obj_t* self) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    free(self);
    assert(0 && "todo: implement");
}

bool is_lisp_type(obj_t* self) {
    return obj_get_type(self) == OBJ_TYPE_LISP_TYPE;
}

obj_lisp_type_t* obj_as_lisp_type(obj_t* self) {
    if (!is_lisp_type(self)) {
        throw(obj_string_new_cstr("expected obj_lisp_type_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_lisp_type_t*) self;
}

ffi_type* obj_lisp_type_to_ffi(obj_t* self) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    assert(0 && "todo: implement");
}

void obj_lisp_type_to_string(obj_t* self, obj_t* string) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_lisp_type_copy(obj_t* self) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    obj_t* copy = obj_lisp_type_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_lisp_type_is_equal(obj_t* self, obj_t* other) {
    obj_lisp_type_t* obj_lisp_type_self = obj_as_lisp_type(self);
    obj_lisp_type_t* obj_lisp_type_other = obj_as_lisp_type(other);
    assert(0 && "todo: implement");
}

bool obj_lisp_type_is_truthy(obj_t* self) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    assert(0 && "todo: implement");
}

size_t obj_lisp_type_hash(obj_t* self) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    assert(0 && "todo: implement");
}

obj_t* obj_lisp_type_eval(obj_t* self, obj_t* env) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    return self;
}

obj_t* obj_lisp_type_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_lisp_type_t* obj_lisp_type = obj_as_lisp_type(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
