#include "universe.h"

obj_env_t* obj_env_new() {
    obj_env_t* self = (obj_env_t*) malloc(sizeof(obj_env_t));
    obj_init((obj_t*) self, OBJ_TYPE_ENV);
    self->hash_table = obj_hash_table_new();
    self->parent = NULL;
    return self;
}

void obj_env_delete(obj_env_t* self) {
    obj_hash_table_delete(self->hash_table);
    free(self);
}

bool is_env(const obj_t* self) {
    return self->type == OBJ_TYPE_ENV;
}

obj_ffi_t* obj_env_to_ffi(const obj_env_t* self) {
    assert(0 && "todo: implement");
}

void obj_env_to_string(const obj_env_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<env ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_t* obj_env_copy(const obj_env_t* self) {
    obj_env_t* copy = obj_env_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_env_equal(const obj_env_t* self, const obj_env_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_env_hash(const obj_env_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_env_eval(const obj_env_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_env_apply(const obj_env_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}

obj_t* obj_env_get(const obj_env_t* self, const obj_t* key) {
    while (self) {
        obj_hash_table_entry_t* entry = obj_hash_table_find(self->hash_table, key);
        if (entry) {
            return entry->value;
        }
        self = self->parent;
    }
    throw(obj_string_new_cstr("key not found"), key);
}

obj_t* obj_env_set(obj_env_t* self, const obj_t* key, obj_t* value) {
    obj_hash_table_entry_t* entry = obj_hash_table_find(self->hash_table, key);
    if (!entry) {
        throw(obj_string_new_cstr("key not found"), key);
    }
    entry->value = value;
    return value;
}

obj_t* obj_env_define(obj_env_t* self, const obj_t* key, obj_t* value) {
    obj_hash_table_insert_result_t insert_result = obj_hash_table_insert(self->hash_table, key, value);
    return insert_result.entry->value;
}
