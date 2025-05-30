#include "obj_string.h"

obj_string_t* obj_string_new(str_t str) {
    obj_string_t* self = (obj_string_t*) malloc(sizeof(obj_string_t));
    obj_init((obj_t*) self, OBJ_TYPE_STRING);
    self->str = str;
    return self;
}

void obj_string_delete(obj_string_t* self) {
    str_delete(&self->str);
    free(self);
}

bool is_string(const obj_t* self) {
    return self->type == OBJ_TYPE_STRING;
}

ffi_type* obj_string_to_ffi_type(const obj_string_t* self) {
    assert(0 && "todo: implement");
}

void obj_string_to_string(const obj_string_t* self, str_t* str) {
    str_push_cstr(str, "<string ", obj_type_to_string(obj_get_type((obj_t*) self)));
    str_push_str(str, &self->str);
    str_push_cstr(str, ">");
}

obj_t* obj_string_copy(const obj_string_t* self) {
    obj_string_t* copy = obj_string_new(str_copy(&self->str));
    return (obj_t*) copy;
}

bool obj_string_equal(const obj_string_t* self, const obj_string_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_string_hash(const obj_string_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_string_eval(const obj_string_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_string_apply(const obj_string_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
