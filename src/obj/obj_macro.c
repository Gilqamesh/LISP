#include "universe.h"

obj_macro_t* obj_macro_new() {
    obj_macro_t* self = (obj_macro_t*) malloc(sizeof(obj_macro_t));
    obj_init((obj_t*) self, OBJ_TYPE_MACRO);
    assert(0 && "todo: implement");
    return self;
}

void obj_macro_delete(obj_macro_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_macro(const obj_t* self) {
    return self->type == OBJ_TYPE_MACRO;
}

obj_ffi_t* obj_macro_to_ffi(const obj_macro_t* self) {
    assert(0 && "todo: implement");
}

void obj_macro_to_string(const obj_macro_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<macro ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_macro_t* obj_macro_copy(const obj_macro_t* self) {
    obj_macro_t* copy = obj_macro_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_macro_equal(const obj_macro_t* self, const obj_macro_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_macro_hash(const obj_macro_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_macro_eval(const obj_macro_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_macro_apply(const obj_macro_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
