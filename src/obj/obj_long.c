#include "universe.h"

obj_long_t* obj_long_new() {
    obj_long_t* self = (obj_long_t*) malloc(sizeof(obj_long_t));
    obj_init((obj_t*) self, OBJ_TYPE_LONG);
    assert(0 && "todo: implement");
    return self;
}

void obj_long_delete(obj_long_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_long(const obj_t* self) {
    return self->type == OBJ_TYPE_LONG;
}

obj_ffi_t* obj_long_to_ffi(const obj_long_t* self) {
    assert(0 && "todo: implement");
}

void obj_long_to_string(const obj_long_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<long ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_long_copy(const obj_long_t* self) {
    obj_long_t* copy = obj_long_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_long_equal(const obj_long_t* self, const obj_long_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_long_hash(const obj_long_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_long_eval(const obj_long_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_long_apply(const obj_long_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
