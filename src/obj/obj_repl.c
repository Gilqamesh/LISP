#include "obj_repl.h"

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

ffi_type* obj_repl_to_ffi_type(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

void obj_repl_to_string(const obj_repl_t* self, str_t* str) {
    str_push_cstr(str, "<repl ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_repl_copy(const obj_repl_t* self) {
    obj_repl_t* copy = obj_repl_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_repl_equal(const obj_repl_t* self, const obj_repl_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_repl_hash(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_repl_eval(const obj_repl_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_repl_apply(const obj_repl_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
