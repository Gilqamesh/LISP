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
    obj_string_push_cstr(str, "<primitive ", obj_type_to_string(obj_get_type((obj_t*) self)));
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "addr2line -f -p -e %s %p", UNIVERSE.argv[0], self->primitive_fn);

    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("popen");
    }
    char buf[512];
    while (fgets(buf, sizeof(buf), fp)) {
        obj_string_push_cstr(str, "%s", buf);
    }
    obj_string_push_cstr(str, ">");
}

obj_primitive_t* obj_primitive_copy(const obj_primitive_t* self) {
    obj_primitive_t* copy = obj_primitive_new(self->strict, self->primitive_fn);
    return copy;
}

bool obj_primitive_equal(const obj_primitive_t* self, const obj_primitive_t* other) {
    return self->primitive_fn == other->primitive_fn && self->strict == other->strict;
}

size_t obj_primitive_hash(const obj_primitive_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_primitive_eval(const obj_primitive_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_primitive_apply(const obj_primitive_t* self, obj_array_t* args, obj_env_t* env) {
    if (self->strict) {
        obj_array_t* evaled_args = obj_array_new();
        for (size_t i = 0; i < obj_array_size(args); ++i) {
            obj_array_push(evaled_args, obj_eval(obj_array_read(args, i), env));
        }
        return self->primitive_fn(self, evaled_args, env);
    } else {
        return self->primitive_fn(self, args, env);
    }
}
