#include "universe.h"

typedef obj_t* obj_array_element_t;

obj_array_t* obj_array_new() {
    obj_array_t* self = (obj_array_t*) malloc(sizeof(obj_array_t));
    obj_init((obj_t*) self, OBJ_TYPE_ARRAY);
    self->objs = darr_new(sizeof(obj_array_element_t));
    return self;
}

void obj_array_delete(obj_array_t* self) {
    darr_delete(&self->objs);
    free(self);
}

bool is_array(const obj_t* self) {
    return self->type == OBJ_TYPE_ARRAY;
}

obj_ffi_t* obj_array_to_ffi(const obj_array_t* self) {
    assert(0 && "todo: implement");
}

void obj_array_to_string(const obj_array_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<array ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_array_copy(const obj_array_t* self) {
    obj_array_t* copy = obj_array_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_array_equal(const obj_array_t* self, const obj_array_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_array_hash(const obj_array_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_array_eval(const obj_array_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_array_apply(const obj_array_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}

obj_t* obj_array_push(obj_array_t* self, obj_t* obj) {
    darr_push(&self->objs, &obj);
    return obj;
}

size_t obj_array_size(const obj_array_t* self) {
    return darr_size(&self->objs);
}

obj_t* obj_array_read(const obj_array_t* self, size_t index) {
    obj_t* result;
    darr_read(&self->objs, index, &result);
    return result;
}

obj_t* obj_array_write(obj_array_t* self, size_t index, obj_t* obj) {
    if (darr_size(&self->objs) <= index) {
        throw(obj_string_new_cstr("Index out of bounds"), obj, (obj_t*) self);
    }
    darr_write(&self->objs, index, &obj);
    return obj;
}
