#include "obj_char.h"

obj_char_t* obj_char_new() {
    obj_char_t* self = (obj_char_t*) malloc(sizeof(obj_char_t));
    obj_init((obj_t*) self, OBJ_TYPE_CHAR);
    assert(0 && "todo: implement");
    return self;
}

void obj_char_delete(obj_char_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_char(const obj_t* self) {
    return self->type == OBJ_TYPE_CHAR;
}

ffi_type* obj_char_to_ffi_type(const obj_char_t* self) {
    assert(0 && "todo: implement");
}

void obj_char_to_string(const obj_char_t* self, str_t* str) {
    str_push_cstr(str, "<char ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_char_copy(const obj_char_t* self) {
    obj_char_t* copy = obj_char_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_char_equal(const obj_char_t* self, const obj_char_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_char_hash(const obj_char_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_char_eval(const obj_char_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_char_apply(const obj_char_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
