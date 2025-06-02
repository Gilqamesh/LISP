#include "universe.h"

obj_t* obj_void_new() {
    obj_void_t* self = (obj_void_t*) malloc(sizeof(obj_void_t));
    obj_init((obj_t*) self, OBJ_TYPE_VOID);
    return (obj_t*) self;
}

void obj_void_delete(obj_t* self) {
    obj_void_t* obj_void = obj_as_void(self);
    free(self);
}

bool is_void(obj_t* self) {
    return self->type == OBJ_TYPE_VOID;
}

obj_void_t* obj_as_void(obj_t* self) {
    if (!is_void(self)) {
        throw(obj_string_new_cstr("expected obj_void_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_void_t*) self;
}

ffi_type* obj_void_to_ffi(obj_t* self) {
    obj_void_t* obj_void = obj_as_void(self);
    assert(0 && "todo: implement");
}

void obj_void_to_string(obj_t* self, obj_t* string) {
    obj_void_t* obj_void = obj_as_void(self);
    obj_string_push_cstr(string, "<%s>", obj_type_to_string(obj_get_type(self)));
}

obj_t* obj_void_copy(obj_t* self) {
    obj_void_t* obj_void = obj_as_void(self);
    obj_t* copy = obj_void_new();
    return copy;
}

bool obj_void_is_equal(obj_t* self, obj_t* other) {
    obj_void_t* obj_void_self = obj_as_void(self);
    obj_void_t* obj_void_other = obj_as_void(other);
    return true;
}

bool obj_void_is_truthy(obj_t* self) {
    obj_void_t* obj_void = obj_as_void(self);
    return false;
}

size_t obj_void_hash(obj_t* self) {
    obj_void_t* obj_void = obj_as_void(self);
    assert(0 && "todo: implement");
}

obj_t* obj_void_eval(obj_t* self, obj_t* env) {
    obj_void_t* obj_void = obj_as_void(self);
    return self;
}

obj_t* obj_void_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_void_t* obj_void = obj_as_void(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
