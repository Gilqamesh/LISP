#include "universe.h"

obj_ushort_t* obj_ushort_new() {
    obj_ushort_t* self = (obj_ushort_t*) malloc(sizeof(obj_ushort_t));
    obj_init((obj_t*) self, OBJ_TYPE_USHORT);
    assert(0 && "todo: implement");
    return self;
}

void obj_ushort_delete(obj_ushort_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_ushort(const obj_t* self) {
    return self->type == OBJ_TYPE_USHORT;
}

obj_ffi_t* obj_ushort_to_ffi(const obj_ushort_t* self) {
    assert(0 && "todo: implement");
}

void obj_ushort_to_string(const obj_ushort_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<ushort ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_ushort_t* obj_ushort_copy(const obj_ushort_t* self) {
    obj_ushort_t* copy = obj_ushort_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_ushort_equal(const obj_ushort_t* self, const obj_ushort_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_ushort_hash(const obj_ushort_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_ushort_eval(const obj_ushort_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_ushort_apply(const obj_ushort_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
