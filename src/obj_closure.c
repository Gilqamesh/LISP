#include "universe.h"

static obj_env_t* obj_env_extend(obj_env_t* self, obj_t* params, obj_t* args);

static obj_env_t* obj_env_extend(obj_env_t* self, obj_t* params, obj_t* args) {
    obj_t* start_params = params;
    obj_t* start_args = args;
    const obj_t* dot = (const obj_t*) obj_symbol_new(obj_string_new_cstr("."));
    obj_env_t* result = obj_env_new();
    result->parent = self;
    while (is_cons(params) && is_cons(args)) {
        if (obj_is_eq(obj_cons_car(params), dot)) {
            params = obj_cons_cdr(params);
            obj_env_define(result, obj_cons_car(params), args);
            return result;
        }
        obj_env_define(result, obj_cons_car(params), obj_cons_car(args));
        params = obj_cons_cdr(params);
        args = obj_cons_cdr(args);
    }

    if (is_nil(params) && is_nil(args)) {
    } else if (is_nil(params) && !is_nil(args)) {
        throw(obj_string_new_cstr("too many arguments"), start_params, start_args);
    } else if (!is_nil(params) && is_nil(args)) {
        if (obj_is_eq(obj_cons_car(params), dot)) {
            obj_env_define(result, obj_cons_car(params), (obj_t*) obj_nil_new());
        } else {
            throw(obj_string_new_cstr("too few arguments"), start_params, start_args);
        }
    } else {
        assert(0);
    }

    return result;
}

obj_closure_t* obj_closure_new(obj_t* params, obj_t* body, obj_env_t* env) {
    obj_closure_t* self = (obj_closure_t*) malloc(sizeof(obj_closure_t));
    obj_init((obj_t*) self, OBJ_TYPE_CLOSURE);
    self->params = params;
    self->body = body;
    self->env = env;
    return self;
}

void obj_closure_delete(obj_closure_t* self) {
    obj_delete(self->params);
    obj_delete(self->body);
    obj_env_delete(self->env);
    free(self);
}

bool is_closure(const obj_t* self) {
    return self->type == OBJ_TYPE_CLOSURE;
}

obj_ffi_t* obj_closure_to_ffi(const obj_closure_t* self) {
    assert(0 && "todo: implement");
}

void obj_closure_to_string(const obj_closure_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(str, "params: ");
    obj_to_string((obj_t*) self->params, str);
    obj_string_push_cstr(str, ", body: ");
    obj_to_string((obj_t*) self->body, str);
    obj_string_push_cstr(str, ", env: ");
    obj_to_string((obj_t*) self->env, str);
    obj_string_push_cstr(str, ">");
}

obj_closure_t* obj_closure_copy(const obj_closure_t* self) {
    obj_closure_t* copy = obj_closure_new(obj_copy(self->params), obj_copy(self->body), obj_env_copy(self->env));
    return copy;
}

bool obj_closure_equal(const obj_closure_t* self, const obj_closure_t* other) {
    assert(0 && "todo: implement");
}

bool obj_closure_is_truthy(const obj_closure_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_closure_hash(const obj_closure_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_closure_eval(const obj_closure_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_closure_apply(const obj_closure_t* self, obj_t* args, obj_env_t* env) {
    // extend env
    // begin on body with extended env
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
