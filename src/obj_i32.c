#include "universe.h"

obj_t* obj_i32_new(int32_t value) {
    obj_i32_t* self = (obj_i32_t*) malloc(sizeof(obj_i32_t));
    obj_init((obj_t*) self, OBJ_TYPE_I32);
    self->value = value;
    return (obj_t*) self;
}

void obj_i32_delete(obj_t* self) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    free(self);
}

bool is_i32(obj_t* self) {
    return self->type == OBJ_TYPE_I32;
}

obj_i32_t* obj_as_i32(obj_t* self) {
    if (!is_i32(self)) {
        throw(obj_string_new_cstr("expected obj_i32_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_i32_t*) self;
}

ffi_type* obj_i32_to_ffi(obj_t* self) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    assert(0 && "todo: implement");
}

void obj_i32_to_string(obj_t* self, obj_t* string) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    obj_string_push_cstr(string, "<%s %d>", obj_type_to_string(obj_get_type(self)), obj_i32->value);
}

obj_t* obj_i32_copy(obj_t* self) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    obj_t* copy = obj_i32_new(obj_i32->value);
    return copy;
}

bool obj_i32_is_equal(obj_t* self, obj_t* other) {
    obj_i32_t* obj_i32_self = obj_as_i32(self);
    obj_i32_t* obj_i32_other = obj_as_i32(other);
    return obj_i32_self->value == obj_i32_other->value;
}

bool obj_i32_is_truthy(obj_t* self) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    return obj_i32->value != 0;
}

size_t obj_i32_hash(obj_t* self) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    return (size_t) obj_i32->value;
}

obj_t* obj_i32_eval(obj_t* self, obj_t* env) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    return self;
}

obj_t* obj_i32_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_i32_t* obj_i32 = obj_as_i32(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
