#include "universe.h"

obj_primitive_t* obj_primitive_new(bool strict, primitive_fn_t primitive_fn) {
    obj_primitive_t* self = (obj_primitive_t*) malloc(sizeof(obj_primitive_t));
    obj_init((obj_t*) self, OBJ_TYPE_PRIMITIVE);
    self->primitive_fn = primitive_fn;
    self->strict = strict;
    return self;
}

void obj_primitive_delete(obj_primitive_t* self) {
    free(self);
}

bool is_primitive(const obj_t* self) {
    return self->type == OBJ_TYPE_PRIMITIVE;
}

obj_ffi_t* obj_primitive_to_ffi(const obj_primitive_t* self) {
    assert(0 && "todo: implement");
}

void obj_primitive_to_string(const obj_primitive_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));


    char buffer[256];
    addr_to_string((void*) self->primitive_fn, buffer, sizeof(buffer));
    obj_string_push_cstr(str, "%s", buffer);
    obj_string_push_cstr(str, ">");
}

obj_primitive_t* obj_primitive_copy(const obj_primitive_t* self) {
    obj_primitive_t* copy = obj_primitive_new(self->strict, self->primitive_fn);
    return copy;
}

bool obj_primitive_equal(const obj_primitive_t* self, const obj_primitive_t* other) {
    return self->primitive_fn == other->primitive_fn && self->strict == other->strict;
}

bool obj_primitive_is_truthy(const obj_primitive_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_primitive_hash(const obj_primitive_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_primitive_eval(const obj_primitive_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_primitive_apply(const obj_primitive_t* self, obj_t* args, obj_env_t* env) {
    if (self->strict) {
        obj_t* evaled_args = obj_cons_map(args, obj_eval, env);
        return self->primitive_fn(self, evaled_args, env);
    } else {
        return self->primitive_fn(self, args, env);
    }
}
