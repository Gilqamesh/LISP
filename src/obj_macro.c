#include "universe.h"

obj_t* obj_macro_new() {
    obj_macro_t* self = (obj_macro_t*) malloc(sizeof(obj_macro_t));
    obj_init((obj_t*) self, OBJ_TYPE_MACRO);
    assert(0 && "todo: implement");
    return (obj_t*) self;
}

void obj_macro_delete(obj_t* self) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    free(self);
    assert(0 && "todo: implement");
}

bool is_macro(obj_t* self) {
    return self->type == OBJ_TYPE_MACRO;
}

obj_macro_t* obj_as_macro(obj_t* self) {
    if (!is_macro(self)) {
        throw(obj_string_new_cstr("expected obj_macro_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_macro_t*) self;
}

ffi_type* obj_macro_to_ffi(obj_t* self) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    assert(0 && "todo: implement");
}

void obj_macro_to_string(obj_t* self, obj_t* string) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_macro_copy(obj_t* self) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    obj_t* copy = obj_macro_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_macro_is_equal(obj_t* self, obj_t* other) {
    obj_macro_t* obj_macro_self = obj_as_macro(self);
    obj_macro_t* obj_macro_other = obj_as_macro(other);
    assert(0 && "todo: implement");
}

bool obj_macro_is_truthy(obj_t* self) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    assert(0 && "todo: implement");
}

size_t obj_macro_hash(obj_t* self) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    assert(0 && "todo: implement");
}

obj_t* obj_macro_eval(obj_t* self, obj_t* env) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    return self;
}

obj_t* obj_macro_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_macro_t* obj_macro = obj_as_macro(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
