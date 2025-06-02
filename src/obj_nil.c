#include "universe.h"

obj_t* obj_nil_new() {
    obj_nil_t* self = (obj_nil_t*) malloc(sizeof(obj_nil_t));
    obj_init((obj_t*) self, OBJ_TYPE_NIL);
    return (obj_t*) self;
}

void obj_nil_delete(obj_t* self) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    free(self);
}

bool is_nil(obj_t* self) {
    return self->type == OBJ_TYPE_NIL;
}

obj_nil_t* obj_as_nil(obj_t* self) {
    if (!is_nil(self)) {
        throw(obj_string_new_cstr("expected obj_nil_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_nil_t*) self;
}

ffi_type* obj_nil_to_ffi(obj_t* self) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    assert(0 && "todo: implement");
}

void obj_nil_to_string(obj_t* self, obj_t* string) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    obj_string_push_cstr(string, "<%s>", obj_type_to_string(obj_get_type(self)));
}

obj_t* obj_nil_copy(obj_t* self) {
    obj_t* copy = obj_nil_new();
    return copy;
}

bool obj_nil_is_equal(obj_t* self, obj_t* other) {
    obj_nil_t* nil_self = obj_as_nil(self);
    obj_nil_t* nil_other = obj_as_nil(other);
    return true;
}

bool obj_nil_is_truthy(obj_t* self) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    return false;
}

size_t obj_nil_hash(obj_t* self) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    assert(0 && "todo: implement");
}

obj_t* obj_nil_eval(obj_t* self, obj_t* env) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    return self;
}

obj_t* obj_nil_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_nil_t* obj_nil = obj_as_nil(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
