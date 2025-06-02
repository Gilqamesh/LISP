#include "universe.h"

obj_t* obj_r64_new(double value) {
    obj_r64_t* self = (obj_r64_t*) malloc(sizeof(obj_r64_t));
    obj_init((obj_t*) self, OBJ_TYPE_R64);
    self->value = value;
    return (obj_t*) self;
}

void obj_r64_delete(obj_t* self) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    free(self);
}

bool is_r64(obj_t* self) {
    return self->type == OBJ_TYPE_R64;
}

obj_r64_t* obj_as_r64(obj_t* self) {
    if (!is_r64(self)) {
        throw(obj_string_new_cstr("expected obj_r64_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_r64_t*) self;
}

ffi_type* obj_r64_to_ffi(obj_t* self) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    assert(0 && "todo: implement");
}

void obj_r64_to_string(obj_t* self, obj_t* string) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    obj_string_push_cstr(string, "<%s %lf>", obj_type_to_string(obj_get_type(self)), obj_r64->value);
}

obj_t* obj_r64_copy(obj_t* self) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    obj_t* copy = obj_r64_new(obj_r64->value);
    return copy;
}

bool obj_r64_is_equal(obj_t* self, obj_t* other) {
    obj_r64_t* obj_r64_self = obj_as_r64(self);
    obj_r64_t* obj_r64_other = obj_as_r64(other);
    return obj_r64_self->value == obj_r64_other->value;
}

bool obj_r64_is_truthy(obj_t* self) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    return obj_r64->value != 0.0;
}

size_t obj_r64_hash(obj_t* self) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    assert(0 && "todo: implement");
}

obj_t* obj_r64_eval(obj_t* self, obj_t* env) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    return self;
}

obj_t* obj_r64_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_r64_t* obj_r64 = obj_as_r64(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
