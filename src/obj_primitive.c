#include "universe.h"

obj_t* obj_primitive_new(bool strict, primitive_fn_t primitive_fn) {
    obj_primitive_t* self = (obj_primitive_t*) malloc(sizeof(obj_primitive_t));
    obj_init((obj_t*) self, OBJ_TYPE_PRIMITIVE);
    self->primitive_fn = primitive_fn;
    self->strict = strict;
    return (obj_t*) self;
}

void obj_primitive_delete(obj_t* self) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    free(self);
}

bool is_primitive(obj_t* self) {
    return self->type == OBJ_TYPE_PRIMITIVE;
}

obj_primitive_t* obj_as_primitive(obj_t* self) {
    if (!is_primitive(self)) {
        throw(obj_string_new_cstr("expected obj_primitive_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_primitive_t*) self;
}

ffi_type* obj_primitive_to_ffi(obj_t* self) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    assert(0 && "todo: implement");
}

void obj_primitive_to_string(obj_t* self, obj_t* string) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));

    char buffer[256];
    addr_to_string((void*) obj_primitive->primitive_fn, buffer, sizeof(buffer));
    obj_string_push_cstr(string, "%s", buffer);
    obj_string_push_cstr(string, ">");
}

obj_t* obj_primitive_copy(obj_t* self) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    obj_t* copy = obj_primitive_new(obj_primitive->strict, obj_primitive->primitive_fn);
    return copy;
}

bool obj_primitive_is_equal(obj_t* self, obj_t* other) {
    obj_primitive_t* obj_primitive_self = obj_as_primitive(self);
    obj_primitive_t* obj_primitive_other = obj_as_primitive((obj_t*) other);
    return obj_primitive_self->primitive_fn == obj_primitive_other->primitive_fn && obj_primitive_self->strict == obj_primitive_other->strict;
}

bool obj_primitive_is_truthy(obj_t* self) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    assert(0 && "todo: implement");
}

size_t obj_primitive_hash(obj_t* self) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    assert(0 && "todo: implement");
}

obj_t* obj_primitive_eval(obj_t* self, obj_t* env) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    return (obj_t*) self;
}

obj_t* obj_primitive_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_primitive_t* obj_primitive = obj_as_primitive(self);
    if (obj_primitive->strict) {
        obj_t* evaled_args = obj_cons_map(args, obj_eval, env);
        return obj_primitive->primitive_fn(self, evaled_args, env);
    } else {
        return obj_primitive->primitive_fn(self, args, env);
    }
}

obj_t* obj_primitive_if(obj_t* self, obj_t* args, obj_t* env) {
    obj_t* evaled_condition = obj_eval(obj_cons_ref(args, 0), env);
    if (obj_is_truthy(evaled_condition)) {
        return obj_eval(obj_cons_ref(args, 1), env);
    } else {
        obj_t* tail = obj_cons_tail(args, 1);
        if (is_cons(tail)) {
            return obj_eval(obj_cons_car(tail), env);
        } else {
            return obj_void_new();
        }
    }
}

obj_t* obj_primitive_lambda(obj_t* self, obj_t* args, obj_t* env) {
    return obj_closure_new(obj_cons_ref(args, 0), obj_cons_ref(args, 1), env);
}
