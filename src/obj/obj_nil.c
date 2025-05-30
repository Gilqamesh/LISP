#include "universe.h"

obj_nil_t* obj_nil_new() {
    obj_nil_t* self = (obj_nil_t*) malloc(sizeof(obj_nil_t));
    obj_init((obj_t*) self, OBJ_TYPE_NIL);
    assert(0 && "todo: implement");
    return self;
}

void obj_nil_delete(obj_nil_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_nil(const obj_t* self) {
    return self->type == OBJ_TYPE_NIL;
}

obj_ffi_t* obj_nil_to_ffi(const obj_nil_t* self) {
    assert(0 && "todo: implement");
}

void obj_nil_to_string(const obj_nil_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<nil ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_nil_copy(const obj_nil_t* self) {
    obj_nil_t* copy = obj_nil_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_nil_equal(const obj_nil_t* self, const obj_nil_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_nil_hash(const obj_nil_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_nil_eval(const obj_nil_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_nil_apply(const obj_nil_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
