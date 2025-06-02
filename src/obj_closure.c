#include "universe.h"

obj_t* obj_closure_new(obj_t* params, obj_t* body, obj_t* env) {
    obj_closure_t* self = (obj_closure_t*) malloc(sizeof(obj_closure_t));
    obj_init((obj_t*) self, OBJ_TYPE_CLOSURE);
    self->params = params;
    self->body = body;
    self->env = env;
    return (obj_t*) self;
}

void obj_closure_delete(obj_t* self) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    obj_cons_delete(obj_closure->params);
    obj_cons_delete(obj_closure->body);
    obj_env_delete(obj_closure->env);
    free(self);
}

bool is_closure(obj_t* self) {
    return self->type == OBJ_TYPE_CLOSURE;
}

obj_closure_t* obj_as_closure(obj_t* self) {
    if (!is_closure(self)) {
        throw(obj_string_new_cstr("expected obj_closure_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_closure_t*) self;
}

ffi_type* obj_closure_to_ffi(obj_t* self) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    assert(0 && "todo: implement");
}

void obj_closure_to_string(obj_t* self, obj_t* string) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_string_push_cstr(string, "params: ");
    obj_to_string(obj_closure->params, string);
    obj_string_push_cstr(string, ", body: ");
    obj_to_string(obj_closure->body, string);
    obj_string_push_cstr(string, ", env: ");
    obj_to_string(obj_closure->env, string);
    obj_string_push_cstr(string, ">");
}

obj_t* obj_closure_copy(obj_t* self) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    obj_t* copy = obj_closure_new(obj_copy(obj_closure->params), obj_copy(obj_closure->body), obj_env_copy(obj_closure->env));
    return copy;
}

bool obj_closure_is_equal(obj_t* self, obj_t* other) {
    obj_closure_t* obj_closure_self = obj_as_closure(self);
    obj_closure_t* obj_closure_other = obj_as_closure(other);
    assert(0 && "todo: implement");
}

bool obj_closure_is_truthy(obj_t* self) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    assert(0 && "todo: implement");
}

size_t obj_closure_hash(obj_t* self) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    assert(0 && "todo: implement");
}

obj_t* obj_closure_eval(obj_t* self, obj_t* env) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    return self;
}

obj_t* obj_closure_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_closure_t* obj_closure = obj_as_closure(self);
    // extend env
    // begin on body with extended env
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
