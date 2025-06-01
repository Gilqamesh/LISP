#include "universe.h"

obj_i64_t* obj_i64_new(int64_t value) {
    obj_i64_t* self = (obj_i64_t*) malloc(sizeof(obj_i64_t));
    obj_init((obj_t*) self, OBJ_TYPE_I64);
    self->value = value;
    return self;
}

void obj_i64_delete(obj_i64_t* self) {
    free(self);
}

bool is_i64(const obj_t* self) {
    return self->type == OBJ_TYPE_I64;
}

obj_ffi_t* obj_i64_to_ffi(const obj_i64_t* self) {
    assert(0 && "todo: implement");
}

void obj_i64_to_string(const obj_i64_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s %lld>", obj_type_to_string(obj_get_type((obj_t*) self)), self->value);
}

obj_i64_t* obj_i64_copy(const obj_i64_t* self) {
    obj_i64_t* copy = obj_i64_new(self->value);
    return copy;
}

bool obj_i64_equal(const obj_i64_t* self, const obj_i64_t* other) {
    return self->value == other->value;
}

bool obj_i64_is_truthy(const obj_i64_t* self) {
    return self->value != 0;
}

size_t obj_i64_hash(const obj_i64_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_i64_eval(const obj_i64_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_i64_apply(const obj_i64_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
