#include "universe.h"

obj_void_t* obj_void_new() {
    obj_void_t* self = (obj_void_t*) malloc(sizeof(obj_void_t));
    obj_init((obj_t*) self, OBJ_TYPE_VOID);
    assert(0 && "todo: implement");
    return self;
}

void obj_void_delete(obj_void_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_void(const obj_t* self) {
    return self->type == OBJ_TYPE_VOID;
}

obj_ffi_t* obj_void_to_ffi(const obj_void_t* self) {
    assert(0 && "todo: implement");
}

void obj_void_to_string(const obj_void_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<void ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_void_copy(const obj_void_t* self) {
    obj_void_t* copy = obj_void_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_void_equal(const obj_void_t* self, const obj_void_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_void_hash(const obj_void_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_void_eval(const obj_void_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_void_apply(const obj_void_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
