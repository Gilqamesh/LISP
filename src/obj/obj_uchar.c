#include "universe.h"

obj_uchar_t* obj_uchar_new() {
    obj_uchar_t* self = (obj_uchar_t*) malloc(sizeof(obj_uchar_t));
    obj_init((obj_t*) self, OBJ_TYPE_UCHAR);
    assert(0 && "todo: implement");
    return self;
}

void obj_uchar_delete(obj_uchar_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_uchar(const obj_t* self) {
    return self->type == OBJ_TYPE_UCHAR;
}

obj_ffi_t* obj_uchar_to_ffi(const obj_uchar_t* self) {
    assert(0 && "todo: implement");
}

void obj_uchar_to_string(const obj_uchar_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<uchar ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_uchar_copy(const obj_uchar_t* self) {
    obj_uchar_t* copy = obj_uchar_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_uchar_equal(const obj_uchar_t* self, const obj_uchar_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_uchar_hash(const obj_uchar_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_uchar_eval(const obj_uchar_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_uchar_apply(const obj_uchar_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
