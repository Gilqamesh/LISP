#include "universe.h"

obj_cons_t* obj_cons_new(obj_t* car, obj_t* cdr) {
    obj_cons_t* self = (obj_cons_t*) malloc(sizeof(obj_cons_t));
    obj_init((obj_t*) self, OBJ_TYPE_CONS);
    self->car = car;
    self->cdr = cdr;
    return self;
}

void obj_cons_delete(obj_cons_t* self) {
    obj_delete(self->car);
    obj_delete(self->cdr);
    free(self);
}

bool is_cons(const obj_t* self) {
    return self->type == OBJ_TYPE_CONS;
}

obj_ffi_t* obj_cons_to_ffi(const obj_cons_t* self) {
    assert(0 && "todo: implement");
}

void obj_cons_to_string(const obj_cons_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_to_string(self->car, other);
    if (is_cons(self->cdr)) {
        obj_string_push_cstr(other, " ");
        obj_to_string(self->cdr, other);
    } else if (is_void(self->cdr)) {
    } else {
        obj_string_push_cstr(other, " . ");
        obj_to_string(self->cdr, other);
    }
    obj_string_push_cstr(other, ">");
}

obj_cons_t* obj_cons_copy(const obj_cons_t* self) {
    obj_cons_t* copy = obj_cons_new(obj_copy(self->car), obj_copy(self->cdr));
    return copy;
}

bool obj_cons_equal(const obj_cons_t* self, const obj_cons_t* other) {
    assert(0 && "todo: implement");
}
bool obj_cons_is_truthy(const obj_cons_t* self) {
    assert(0 && "todo: implement");
}

size_t obj_cons_hash(const obj_cons_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_cons_eval(const obj_cons_t* self, obj_env_t* env) {
    obj_t* evaled_car = obj_eval(self->car, env);
    obj_t* args = self->cdr;
    return obj_apply(evaled_car, args, env);
}

obj_t* obj_cons_apply(const obj_cons_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}

obj_t* obj_cons_car(const obj_t* self) {
    if (!is_cons(self)) {
        throw(obj_string_new_cstr("not a cons"), (obj_t*) self);
    }
    return ((const obj_cons_t*) self)->car;
}

obj_t* obj_cons_cdr(const obj_t* self) {
    if (!is_cons(self)) {
        throw(obj_string_new_cstr("not a cons"), (obj_t*) self);
    }
    return ((const obj_cons_t*) self)->cdr;
}

obj_t* obj_cons_ref(const obj_t* self, size_t index) {
    return obj_cons_car(obj_cons_tail(self, index));
}

obj_t* obj_cons_tail(const obj_t* self, size_t index) {
    const obj_t* start = self;
    while (is_cons(self) && index) {
        self = obj_cons_cdr(self);
        --index;
    }
    if (index) {
        throw(obj_string_new_cstr("index out of bounds"), (obj_t*) start);
    }
    return obj_cons_cdr(self);
}

obj_t* obj_cons_for_each(const obj_t* self, obj_t* (*fn)(const obj_t* obj, obj_env_t* env), obj_env_t* env) {
    obj_t* result = NULL;
    const obj_t* current = self;
    while (is_cons(current)) {
        result = fn(obj_cons_car(current), env);
        current = obj_cons_cdr(current);
    }
    if (!is_void(obj_cons_cdr(current))) {
        throw(obj_string_new_cstr("not a list"), self);
    }
    return result;
}

obj_t* obj_cons_map(const obj_t* self, obj_t* (*fn)(const obj_t* obj, obj_env_t* env), obj_env_t* env) {
    obj_t* result = NULL;
    obj_t** head = &result;
    const obj_t* cur = self;

    while (is_cons(cur)) {
        *head = (obj_t*) obj_cons_new(fn(obj_cons_car(cur), env), NULL);
        head = &(*((obj_cons_t**) head))->cdr;
        cur = obj_cons_cdr(cur);
    }

    if (is_void(cur)) {
        *head = (obj_t*) obj_void_new();
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }

    return result;
}

obj_t* obj_cons_filter(const obj_t* self, bool (*predicate)(const obj_t* obj, obj_env_t* env), obj_env_t* env) {
    obj_t* result = NULL;
    obj_t** head = &result;
    const obj_t* cur = self;

    while (is_cons(cur)) {
        const obj_t* car = obj_cons_car(cur);
        if (predicate(car, env)) {
            *head = (obj_t*) obj_cons_new(obj_copy(car), NULL);
            head = &((*(obj_cons_t**) head)->cdr);
        }
        cur = obj_cons_cdr(cur);
    }

    if (is_void(cur)) {
        *head = (obj_t*) obj_void_new();
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }

    return result;
}

obj_t* obj_cons_fold_left(const obj_t* self, obj_t* (*combiner)(const obj_t* obj, obj_t* acc, obj_env_t* env), obj_t* acc, obj_env_t* env) {
    const obj_t* current = self;
    while (is_cons(current)) {
        acc = combiner(obj_cons_car(current), acc, env);
        current = obj_cons_cdr(current);
    }
    if (is_void(current)) {
        return acc;
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }
}

obj_t* obj_cons_fold_right(const obj_t* self, obj_t* (*combiner)(const obj_t* obj, obj_t* acc, obj_env_t* env), obj_t* acc, obj_env_t* env) {
    if (is_void(self)) {
        return acc;
    } else if (is_cons(self)) {
        return obj_cons_fold_right(obj_cons_cdr(self), combiner, combiner(obj_cons_car(self), acc, env), env);
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }
}
