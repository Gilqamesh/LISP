#include "obj_env.h"

obj_env_t* obj_env_new() {
    obj_env_t* self = (obj_env_t*) malloc(sizeof(obj_env_t));
    obj_init((obj_t*) self, OBJ_TYPE_ENV);
    assert(0 && "todo: implement");
    return self;
}

void obj_env_delete(obj_env_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_env(const obj_t* self) {
    return self->type == OBJ_TYPE_ENV;
}

ffi_type* obj_env_to_ffi_type(const obj_env_t* self) {
    assert(0 && "todo: implement");
}

void obj_env_to_string(const obj_env_t* self, str_t* str) {
    str_push_cstr(str, "<env ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_env_copy(const obj_env_t* self) {
    obj_env_t* copy = obj_env_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_env_equal(const obj_env_t* self, const obj_env_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_env_hash(const obj_env_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_env_eval(const obj_env_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_env_apply(const obj_env_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
