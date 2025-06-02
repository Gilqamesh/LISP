#include "universe.h"

obj_t* obj_ffi_new() {
    obj_t* self = (obj_t*) malloc(sizeof(obj_ffi_t));
    obj_init((obj_t*) self, OBJ_TYPE_FFI);
    assert(0 && "todo: implement");
    return self;
}

void obj_ffi_delete(obj_t* self) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    free(self);
    assert(0 && "todo: implement");
}

bool is_ffi(obj_t* self) {
    return self->type == OBJ_TYPE_FFI;
}

obj_ffi_t* obj_as_ffi(obj_t* self) {
    if (!is_ffi(self)) {
        throw(obj_string_new_cstr("expected obj_ffi_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_ffi_t*) self;
}

ffi_type* obj_ffi_to_ffi(obj_t* self) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    assert(0 && "todo: implement");
}

void obj_ffi_to_string(obj_t* self, obj_t* string) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_ffi_copy(obj_t* self) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    obj_t* copy = obj_ffi_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_ffi_is_equal(obj_t* self, obj_t* other) {
    obj_ffi_t* obj_ffi_self = obj_as_ffi(self);
    obj_ffi_t* obj_ffi_other = obj_as_ffi(other);
    assert(0 && "todo: implement");
}

bool obj_ffi_is_truthy(obj_t* self) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    assert(0 && "todo: implement");
}

size_t obj_ffi_hash(obj_t* self) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    assert(0 && "todo: implement");
}

obj_t* obj_ffi_eval(obj_t* self, obj_t* env) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    return self;
}

obj_t* obj_ffi_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_ffi_t* obj_ffi = obj_as_ffi(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
