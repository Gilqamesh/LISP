#include "universe.h"

obj_primitive_t* obj_primitive_new() {
    obj_primitive_t* self = (obj_primitive_t*) malloc(sizeof(obj_primitive_t));
    obj_init((obj_t*) self, OBJ_TYPE_PRIMITIVE);
    assert(0 && "todo: implement");
    return self;
}

void obj_primitive_delete(obj_primitive_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_primitive(const obj_t* self) {
    return self->type == OBJ_TYPE_PRIMITIVE;
}

obj_ffi_t* obj_primitive_to_ffi(const obj_primitive_t* self) {
    assert(0 && "todo: implement");
}

void obj_primitive_to_string(const obj_primitive_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<primitive ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_primitive_copy(const obj_primitive_t* self) {
    obj_primitive_t* copy = obj_primitive_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_primitive_equal(const obj_primitive_t* self, const obj_primitive_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_primitive_hash(const obj_primitive_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_primitive_eval(const obj_primitive_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_primitive_apply(const obj_primitive_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
