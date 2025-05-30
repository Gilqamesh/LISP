#include "universe.h"

obj_bool_t* obj_bool_new() {
    obj_bool_t* self = (obj_bool_t*) malloc(sizeof(obj_bool_t));
    obj_init((obj_t*) self, OBJ_TYPE_BOOL);
    assert(0 && "todo: implement");
    return self;
}

void obj_bool_delete(obj_bool_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_bool(const obj_t* self) {
    return self->type == OBJ_TYPE_BOOL;
}

obj_ffi_t* obj_bool_to_ffi(const obj_bool_t* self) {
    assert(0 && "todo: implement");
}

void obj_bool_to_string(const obj_bool_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<bool ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_bool_copy(const obj_bool_t* self) {
    obj_bool_t* copy = obj_bool_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_bool_equal(const obj_bool_t* self, const obj_bool_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_bool_hash(const obj_bool_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_bool_eval(const obj_bool_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_bool_apply(const obj_bool_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
