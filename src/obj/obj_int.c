#include "obj_int.h"
#include "universe.h"

obj_int_t* obj_int_new(int integer) {
    obj_int_t* self = (obj_int_t*) malloc(sizeof(obj_int_t));
    obj_init((obj_t*) self, OBJ_TYPE_INT);
    self->integer = integer;
    return self;
}

void obj_int_delete(obj_int_t* self) {
    free(self);
}

bool is_int(const obj_t* self) {
    return self->type == OBJ_TYPE_INT;
}

obj_ffi_t* obj_int_to_ffi(const obj_int_t* self) {
    assert(0 && "todo: implement");
}

void obj_int_to_string(const obj_int_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<int ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_int_t* obj_int_copy(const obj_int_t* self) {
    obj_int_t* copy = obj_int_new(self->integer);
    return copy;
}

bool obj_int_equal(const obj_int_t* self, const obj_int_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_int_hash(const obj_int_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_int_eval(const obj_int_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_int_apply(const obj_int_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
