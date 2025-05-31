#include "universe.h"

obj_short_t* obj_short_new() {
    obj_short_t* self = (obj_short_t*) malloc(sizeof(obj_short_t));
    obj_init((obj_t*) self, OBJ_TYPE_SHORT);
    assert(0 && "todo: implement");
    return self;
}

void obj_short_delete(obj_short_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_short(const obj_t* self) {
    return self->type == OBJ_TYPE_SHORT;
}

obj_ffi_t* obj_short_to_ffi(const obj_short_t* self) {
    assert(0 && "todo: implement");
}

void obj_short_to_string(const obj_short_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<short ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_short_copy(const obj_short_t* self) {
    obj_short_t* copy = obj_short_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_short_equal(const obj_short_t* self, const obj_short_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_short_hash(const obj_short_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_short_eval(const obj_short_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_short_apply(const obj_short_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
