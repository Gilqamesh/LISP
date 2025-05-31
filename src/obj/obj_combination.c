#include "universe.h"

obj_combination_t* obj_combination_new(obj_t* unevaluated_op, obj_array_t* unevaluated_args) {
    obj_combination_t* self = (obj_combination_t*) malloc(sizeof(obj_combination_t));
    obj_init((obj_t*) self, OBJ_TYPE_COMBINATION);
    self->unevaluated_op = unevaluated_op;
    self->unevaluated_args = unevaluated_args;
    return self;
}

void obj_combination_delete(obj_combination_t* self) {
    if (self->unevaluated_op) {
        obj_delete(self->unevaluated_op);
    }
    if (self->unevaluated_args) {
        obj_array_delete(self->unevaluated_args);
    }
    free(self);
}

bool is_combination(const obj_t* self) {
    return self->type == OBJ_TYPE_COMBINATION;
}

obj_ffi_t* obj_combination_to_ffi(const obj_combination_t* self) {
    assert(0 && "todo: implement");
}

void obj_combination_to_string(const obj_combination_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<combination ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(other, "op: ");
    obj_to_string(self->unevaluated_op, other);
    obj_string_push_cstr(other, ", args: [");
    for (size_t i = 0; i < obj_array_size(self->unevaluated_args); ++i) {
        obj_to_string(obj_array_read(self->unevaluated_args, i), other);
        if (i + 1 < obj_array_size(self->unevaluated_args)) {
            obj_string_push_cstr(other, ", ");
        }
    }
    obj_string_push_cstr(other, ">");
}

obj_combination_t* obj_combination_copy(const obj_combination_t* self) {
    obj_combination_t* copy = obj_combination_new(
        obj_copy(self->unevaluated_op),
        obj_array_copy(self->unevaluated_args)
    );
    assert(0 && "todo: implement");
    return copy;
}

bool obj_combination_equal(const obj_combination_t* self, const obj_combination_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_combination_hash(const obj_combination_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_combination_eval(const obj_combination_t* self, obj_env_t* env) {
    obj_t* evaluated_op = obj_eval(self->unevaluated_op, env);
    obj_t* result = obj_apply(evaluated_op, self->unevaluated_args, env);
    return result;
}

obj_t* obj_combination_apply(const obj_combination_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}
