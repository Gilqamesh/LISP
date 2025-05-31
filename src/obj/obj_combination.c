#include "universe.h"

obj_combination_t* obj_combination_new() {
    obj_combination_t* self = (obj_combination_t*) malloc(sizeof(obj_combination_t));
    obj_init((obj_t*) self, OBJ_TYPE_COMBINATION);
    assert(0 && "todo: implement");
    return self;
}

void obj_combination_delete(obj_combination_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_combination(const obj_t* self) {
    return self->type == OBJ_TYPE_COMBINATION;
}

obj_ffi_t* obj_combination_to_ffi(const obj_combination_t* self) {
    assert(0 && "todo: implement");
}

void obj_combination_to_string(const obj_combination_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<combination ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(other, ">");
}

obj_t* obj_combination_copy(const obj_combination_t* self) {
    obj_combination_t* copy = obj_combination_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_combination_equal(const obj_combination_t* self, const obj_combination_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_combination_hash(const obj_combination_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_combination_eval(const obj_combination_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_combination_apply(const obj_combination_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
