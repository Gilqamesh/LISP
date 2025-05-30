#include "obj_ulong.h"

obj_ulong_t* obj_ulong_new() {
    obj_ulong_t* self = (obj_ulong_t*) malloc(sizeof(obj_ulong_t));
    obj_init((obj_t*) self, OBJ_TYPE_ULONG);
    assert(0 && "todo: implement");
    return self;
}

void obj_ulong_delete(obj_ulong_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_ulong(const obj_t* self) {
    return self->type == OBJ_TYPE_ULONG;
}

ffi_type* obj_ulong_to_ffi_type(const obj_ulong_t* self) {
    assert(0 && "todo: implement");
}

void obj_ulong_to_string(const obj_ulong_t* self, str_t* str) {
    str_push_cstr(str, "<ulong ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_ulong_copy(const obj_ulong_t* self) {
    obj_ulong_t* copy = obj_ulong_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_ulong_equal(const obj_ulong_t* self, const obj_ulong_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_ulong_hash(const obj_ulong_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_ulong_eval(const obj_ulong_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_ulong_apply(const obj_ulong_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
