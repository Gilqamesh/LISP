#include "universe.h"

obj_t* obj_env_new() {
    obj_env_t* self = (obj_env_t*) malloc(sizeof(obj_env_t));
    obj_init((obj_t*) self, OBJ_TYPE_ENV);
    self->hash_table = obj_hash_table_new();
    self->parent = obj_nil_new();
    return (obj_t*) self;
}

void obj_env_delete(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    obj_hash_table_delete(obj_env->hash_table);
    free(self);
}

bool is_env(obj_t* self) {
    return self->type == OBJ_TYPE_ENV;
}

obj_env_t* obj_as_env(obj_t* self) {
    if (!is_env(self)) {
        throw(obj_string_new_cstr("expected obj_env_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_env_t*) self;
}

ffi_type* obj_env_to_ffi(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    assert(0 && "todo: implement");
}

void obj_env_to_string(obj_t* self, obj_t* string) {
    obj_env_t* obj_env = obj_as_env(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_env_copy(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    obj_t* copy = obj_env_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_env_is_equal(obj_t* self, obj_t* other) {
    obj_env_t* obj_env_self = obj_as_env(self);
    obj_env_t* obj_env_other = obj_as_env(other);
    assert(0 && "todo: implement");
}

bool obj_env_is_truthy(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    assert(0 && "todo: implement");
}

size_t obj_env_hash(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    assert(0 && "todo: implement");
}

obj_t* obj_env_eval(obj_t* self, obj_t* env) {
    obj_env_t* obj_env = obj_as_env(self);
    return self;
}

obj_t* obj_env_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_env_t* obj_env = obj_as_env(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

obj_t* obj_env_set_parent(obj_t* self, obj_t* parent) {
    obj_env_t* obj_env = obj_as_env(self);
    obj_env->parent = parent;
    return self;
}

obj_t* obj_env_get_parent(obj_t* self) {
    obj_env_t* obj_env = obj_as_env(self);
    return obj_env->parent;
}

obj_t* obj_env_get(obj_t* self, obj_t* key) {
    obj_env_t* obj_env = obj_as_env(self);
    while (!is_nil(self)) {
        hash_table_entry_t* entry = obj_hash_table_find(obj_as_env(self)->hash_table, key);
        if (entry) {
            return entry->value;
        }
        self = obj_env_get_parent(self);
    }
    throw(obj_string_new_cstr("undefined key"), key, self);
}

obj_t* obj_env_set(obj_t* self, obj_t* key, obj_t* value) {
    obj_env_t* obj_env = obj_as_env(self);
    while (!is_nil(self)) {
        hash_table_entry_t* entry = obj_hash_table_find(obj_as_env(self)->hash_table, key);
        if (entry) {
            entry->value = value;
            return entry->value;
        }
        self = obj_env_get_parent(self);
    }
    throw(obj_string_new_cstr("undefined key"), key);
}

obj_t* obj_env_define(obj_t* self, obj_t* key, obj_t* value) {
    obj_env_t* obj_env = obj_as_env(self);
    hash_table_insert_result_t insert_result = obj_hash_table_insert(obj_env->hash_table, key, value);
    return insert_result.entry->value;
}

obj_t* obj_env_extend(obj_t* self, obj_t* params, obj_t* args) {
    obj_t* start_params = params;
    obj_t* start_args = args;
    obj_t* dot = obj_symbol_new(obj_string_new_cstr("."));
    obj_t* result = obj_env_new();
    obj_env_set_parent(result, self);
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
            obj_env_define(result, obj_cons_car(params), obj_nil_new());
        } else {
            throw(obj_string_new_cstr("too few arguments"), start_params, start_args);
        }
    } else {
        assert(0);
    }

    return result;
}
