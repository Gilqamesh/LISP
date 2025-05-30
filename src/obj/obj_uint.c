#include "obj_uint.h"

obj_uint_t* obj_uint_new() {
    obj_uint_t* self = (obj_uint_t*) malloc(sizeof(obj_uint_t));
    obj_init((obj_t*) self, OBJ_TYPE_UINT);
    assert(0 && "todo: implement");
    return self;
}

void obj_uint_delete(obj_uint_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_uint(const obj_t* self) {
    return self->type == OBJ_TYPE_UINT;
}

ffi_type* obj_uint_to_ffi_type(const obj_uint_t* self) {
    assert(0 && "todo: implement");
}

void obj_uint_to_string(const obj_uint_t* self, str_t* str) {
    str_push_cstr(str, "<uint ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_uint_copy(const obj_uint_t* self) {
    obj_uint_t* copy = obj_uint_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_uint_equal(const obj_uint_t* self, const obj_uint_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_uint_hash(const obj_uint_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_uint_eval(const obj_uint_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_uint_apply(const obj_uint_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
