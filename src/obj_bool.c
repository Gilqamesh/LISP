#include "universe.h"

obj_t* obj_bool_new(bool value) {
    obj_bool_t* self = (obj_bool_t*) malloc(sizeof(obj_bool_t));
    obj_init((obj_t*) self, OBJ_TYPE_BOOL);
    self->value = value;
    return (obj_t*) self;
}

void obj_bool_delete(obj_t* self) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    free(self);
}

bool is_bool(obj_t* self) {
    return self->type == OBJ_TYPE_BOOL;
}

obj_bool_t* obj_as_bool(obj_t* self) {
    if (!is_bool(self)) {
        throw(obj_string_new_cstr("expected obj_bool_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_bool_t*) self;
}

ffi_type* obj_bool_to_ffi(obj_t* self) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    assert(0 && "todo: implement");
}

void obj_bool_to_string(obj_t* self, obj_t* string) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    obj_string_push_cstr(string, "<%s %s>", obj_type_to_string(obj_get_type(self)), obj_bool->value ? "true" : "false");
}

obj_t* obj_bool_copy(obj_t* self) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    obj_t* copy = obj_bool_new(obj_bool->value);
    return copy;
}

bool obj_bool_is_equal(obj_t* self, obj_t* other) {
    obj_bool_t* obj_bool_self = obj_as_bool(self);
    obj_bool_t* obj_bool_other = obj_as_bool(other);
    return obj_bool_self->value == obj_bool_other->value;
}

bool obj_bool_is_truthy(obj_t* self) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    return obj_bool->value;
}

size_t obj_bool_hash(obj_t* self) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    assert(0 && "todo: implement");
}

obj_t* obj_bool_eval(obj_t* self, obj_t* env) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    return self;
}

obj_t* obj_bool_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_bool_t* obj_bool = obj_as_bool(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
