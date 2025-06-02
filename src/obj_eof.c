#include "universe.h"

obj_t* obj_eof_new() {
    obj_eof_t* self = (obj_eof_t*) malloc(sizeof(obj_eof_t));
    obj_init((obj_t*) self, OBJ_TYPE_EOF);
    return (obj_t*) self;
}

void obj_eof_delete(obj_t* self) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    free(self);
}

bool is_eof(obj_t* self) {
    return self->type == OBJ_TYPE_EOF;
}

obj_eof_t* obj_as_eof(obj_t* self) {
    if (!is_eof(self)) {
        throw(obj_string_new_cstr("expected obj_eof_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_eof_t*) self;
}

ffi_type* obj_eof_to_ffi(obj_t* self) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    assert(0 && "todo: implement");
}

void obj_eof_to_string(obj_t* self, obj_t* string) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    obj_string_push_cstr(string, "<%s>", obj_type_to_string(obj_get_type(self)));
}

obj_t* obj_eof_copy(obj_t* self) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    obj_t* copy = obj_eof_new();
    return copy;
}

bool obj_eof_is_equal(obj_t* self, obj_t* other) {
    obj_eof_t* eof_self = obj_as_eof(self);
    obj_eof_t* eof_other = obj_as_eof(other);
    assert(0 && "todo: implement");
}

bool obj_eof_is_truthy(obj_t* self) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    assert(0 && "todo: implement");
}

size_t obj_eof_hash(obj_t* self) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    assert(0 && "todo: implement");
}

obj_t* obj_eof_eval(obj_t* self, obj_t* env) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    return self;
}

obj_t* obj_eof_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_eof_t* obj_eof = obj_as_eof(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
