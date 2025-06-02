#include "universe.h"

obj_t* obj_cons_new(obj_t* car, obj_t* cdr) {
    obj_cons_t* self = (obj_cons_t*) malloc(sizeof(obj_cons_t));
    obj_init((obj_t*) self, OBJ_TYPE_CONS);
    self->car = car;
    self->cdr = cdr;
    return (obj_t*) self;
}

void obj_cons_delete(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_delete(obj_cons->car);
    obj_delete(obj_cons->cdr);
    free(self);
}

bool is_cons(obj_t* self) {
    return self->type == OBJ_TYPE_CONS;
}

obj_cons_t* obj_as_cons(obj_t* self) {
    if (!is_cons(self)) {
        throw(obj_string_new_cstr("expected obj_cons_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_cons_t*) self;
}

ffi_type* obj_cons_to_ffi(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    assert(0 && "todo: implement");
}

void obj_cons_to_string(obj_t* self, obj_t* string) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_to_string(obj_cons->car, string);
    if (is_cons(obj_cons->cdr)) {
        obj_string_push_cstr(string, " ");
        obj_to_string(obj_cons->cdr, string);
    } else if (is_void(obj_cons->cdr)) {
    } else {
        obj_string_push_cstr(string, " . ");
        obj_to_string(obj_cons->cdr, string);
    }
    obj_string_push_cstr(string, ">");
}

obj_t* obj_cons_copy(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* copy = obj_cons_new(obj_copy(obj_cons->car), obj_copy(obj_cons->cdr));
    return copy;
}

bool obj_cons_is_equal(obj_t* self, obj_t* other) {
    obj_cons_t* cons_self = obj_as_cons(self);
    obj_cons_t* cons_other = obj_as_cons(other);
    assert(0 && "todo: implement");
}
bool obj_cons_is_truthy(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    assert(0 && "todo: implement");
}

size_t obj_cons_hash(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    assert(0 && "todo: implement");
}

obj_t* obj_cons_eval(obj_t* self, obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* evaled_car = obj_eval(obj_cons->car, env);
    obj_t* args = obj_cons->cdr;
    return obj_apply(evaled_car, args, env);
}

obj_t* obj_cons_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

obj_t* obj_cons_car(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    return obj_cons->car;
}

obj_t* obj_cons_cdr(obj_t* self) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    return obj_cons->cdr;
}

obj_t* obj_cons_ref(obj_t* self, size_t index) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    return obj_cons_car(obj_cons_tail(self, index));
}

obj_t* obj_cons_tail(obj_t* self, size_t index) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* start = self;
    while (is_cons(self) && index) {
        self = obj_cons_cdr(self);
        --index;
    }
    if (index) {
        throw(obj_string_new_cstr("index out of bounds"), start);
    }
    return obj_cons_cdr(self);
}

obj_t* obj_cons_for_each(obj_t* self, obj_t* (*fn)(obj_t* obj, obj_t* env), obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* result = NULL;
    obj_t* current = self;
    while (is_cons(current)) {
        result = fn(obj_cons_car(current), env);
        current = obj_cons_cdr(current);
    }
    if (!is_void(obj_cons_cdr(current))) {
        throw(obj_string_new_cstr("not a list"), self);
    }
    return result;
}

obj_t* obj_cons_map(obj_t* self, obj_t* (*fn)(obj_t* obj, obj_t* env), obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* result = NULL;
    obj_t** head = &result;
    obj_t* cur = self;

    while (is_cons(cur)) {
        *head = obj_cons_new(fn(obj_cons_car(cur), env), NULL);
        head = &obj_as_cons(*head)->cdr;
        cur = obj_cons_cdr(cur);
    }

    if (is_void(cur)) {
        *head = obj_void_new();
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }

    return result;
}

obj_t* obj_cons_filter(obj_t* self, bool (*predicate)(obj_t* obj, obj_t* env), obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* result = NULL;
    obj_t** head = &result;
    obj_t* cur = self;

    while (is_cons(cur)) {
        obj_t* car = obj_cons_car(cur);
        if (predicate(car, env)) {
            *head = obj_cons_new(obj_copy(car), NULL);
            head = &obj_as_cons(*head)->cdr;
        }
        cur = obj_cons_cdr(cur);
    }

    if (is_void(cur)) {
        *head = obj_void_new();
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }

    return result;
}

obj_t* obj_cons_fold_left(obj_t* self, obj_t* (*combiner)(obj_t* obj, obj_t* acc, obj_t* env), obj_t* acc, obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    obj_t* current = self;
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

obj_t* obj_cons_fold_right(obj_t* self, obj_t* (*combiner)(obj_t* obj, obj_t* acc, obj_t* env), obj_t* acc, obj_t* env) {
    obj_cons_t* obj_cons = obj_as_cons(self);
    if (is_void(self)) {
        return acc;
    } else if (is_cons(self)) {
        return obj_cons_fold_right(obj_cons_cdr(self), combiner, combiner(obj_cons_car(self), acc, env), env);
    } else {
        throw(obj_string_new_cstr("not a list"), self);
    }
}
