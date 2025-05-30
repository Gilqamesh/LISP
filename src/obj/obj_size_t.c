#include "universe.h"

obj_size_t_t* obj_size_t_new(size_t value) {
    obj_size_t_t* self = (obj_size_t_t*) malloc(sizeof(obj_size_t_t));
    obj_init((obj_t*) self, OBJ_TYPE_SIZE_T);
    self->value = value;
    return self;
}

void obj_size_t_delete(obj_size_t_t* self) {
    free(self);
}

bool is_size_t(const obj_t* self) {
    return self->type == OBJ_TYPE_SIZE_T;
}

obj_ffi_t* obj_size_t_to_ffi(const obj_size_t_t* self) {
    assert(0 && "todo: implement");
}

void obj_size_t_to_string(const obj_size_t_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<size_t ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(other, "%zu", self->value);
    obj_string_push_cstr(other, ">");
}

obj_t* obj_size_t_copy(const obj_size_t_t* self) {
    obj_size_t_t* copy = obj_size_t_new(self->value);
    return (obj_t*) copy;
}

bool obj_size_t_equal(const obj_size_t_t* self, const obj_size_t_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_size_t_hash(const obj_size_t_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_size_t_eval(const obj_size_t_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_size_t_apply(const obj_size_t_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
