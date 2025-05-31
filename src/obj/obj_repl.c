#include "universe.h"

obj_repl_t* obj_repl_new() {
    obj_repl_t* self = (obj_repl_t*) malloc(sizeof(obj_repl_t));
    obj_init((obj_t*) self, OBJ_TYPE_REPL);
    assert(0 && "todo: implement");
    return self;
}

void obj_repl_delete(obj_repl_t* self) {
    free(self);
    assert(0 && "todo: implement");
}

bool is_repl(const obj_t* self) {
    return self->type == OBJ_TYPE_REPL;
}

obj_ffi_t* obj_repl_to_ffi(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

void obj_repl_to_string(const obj_repl_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<repl ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_repl_t* obj_repl_copy(const obj_repl_t* self) {
    obj_repl_t* copy = obj_repl_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_repl_equal(const obj_repl_t* self, const obj_repl_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_repl_hash(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_repl_eval(const obj_repl_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_repl_apply(const obj_repl_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
