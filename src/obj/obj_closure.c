#include "obj_closure.h"

obj_closure_t* obj_closure_new() {
    obj_closure_t* self = (obj_closure_t*) malloc(sizeof(obj_closure_t));
    obj_init((obj_t*) self, OBJ_TYPE_CLOSURE);
    assert(0 && "todo: implement");
    return self;
}

void obj_closure_delete(obj_closure_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_closure(const obj_t* self) {
    return self->type == OBJ_TYPE_CLOSURE;
}

ffi_type* obj_closure_to_ffi_type(const obj_closure_t* self) {
    assert(0 && "todo: implement");
}

void obj_closure_to_string(const obj_closure_t* self, str_t* str) {
    str_push_cstr(str, "<closure ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_closure_copy(const obj_closure_t* self) {
    obj_closure_t* copy = obj_closure_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_closure_equal(const obj_closure_t* self, const obj_closure_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_closure_hash(const obj_closure_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_closure_eval(const obj_closure_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_closure_apply(const obj_closure_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
