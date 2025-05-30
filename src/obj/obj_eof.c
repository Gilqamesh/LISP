#include "universe.h"

obj_eof_t* obj_eof_new() {
    obj_eof_t* self = (obj_eof_t*) malloc(sizeof(obj_eof_t));
    obj_init((obj_t*) self, OBJ_TYPE_EOF);
    assert(0 && "todo: implement");
    return self;
}

void obj_eof_delete(obj_eof_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_eof(const obj_t* self) {
    return self->type == OBJ_TYPE_EOF;
}

obj_ffi_t* obj_eof_to_ffi(const obj_eof_t* self) {
    assert(0 && "todo: implement");
}

void obj_eof_to_string(const obj_eof_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<eof ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_eof_copy(const obj_eof_t* self) {
    obj_eof_t* copy = obj_eof_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_eof_equal(const obj_eof_t* self, const obj_eof_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_eof_hash(const obj_eof_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_eof_eval(const obj_eof_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_eof_apply(const obj_eof_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
