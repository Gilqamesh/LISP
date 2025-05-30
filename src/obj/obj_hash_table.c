#include "obj_hash_table.h"

#include "obj_error.h"

obj_hash_table_t* obj_hash_table_new() {
    obj_hash_table_t* self = (obj_hash_table_t*) malloc(sizeof(obj_hash_table_t));
    obj_init((obj_t*) self, OBJ_TYPE_HASH_TABLE);
    self->hash_table = hash_table_new(
        sizeof(obj_t*), sizeof(obj_t*),
        (size_t (*)(const void*)) obj_hash,
        (bool (*)(const void*, const void*)) obj_equal
    );
    self->parent = NULL;
    return self;
}

void obj_hash_table_delete(obj_hash_table_t* self) {
    hash_table_delete(&self->hash_table);
    free(self);
}

bool is_hash_table(const obj_t* self) {
    return self->type == OBJ_TYPE_HASH_TABLE;
}

ffi_type* obj_hash_table_to_ffi_type(const obj_hash_table_t* self) {
    assert(0 && "todo: implement");
}

void obj_hash_table_to_string(const obj_hash_table_t* self, str_t* str) {
    str_push_cstr(str, "<hash_table ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    str_push_cstr(str, ">");
}

obj_t* obj_hash_table_copy(const obj_hash_table_t* self) {
    obj_hash_table_t* copy = obj_hash_table_new();
    assert(0 && "todo: implement");
    return (obj_t*) copy;
}

bool obj_hash_table_equal(const obj_hash_table_t* self, const obj_hash_table_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_hash_table_hash(const obj_hash_table_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_hash_table_eval(const obj_hash_table_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_hash_table_apply(const obj_hash_table_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}

obj_t* obj_hash_table_get(const obj_hash_table_t* self, const obj_t* key) {
    while (self) {
        hash_table_entry_t* entry = hash_table_find(&self->hash_table, key);
        if (entry) {
            return *(obj_t**) hash_table_entry_value(&self->hash_table, entry);
        }
        self = self->parent;
    }
    throw(str_new_cstr("key not found in hash table"), key);
}

obj_t* obj_hash_table_set(obj_hash_table_t* self, const obj_t* key, const obj_t* value) {
    if (!self) {
        throw(str_new_cstr("hash table is NULL"), key, value);
    }

    hash_table_insert_result_t insert_result = hash_table_insert(&self->hash_table, &key, &value);
    return *(obj_t**) hash_table_entry_value(&self->hash_table, insert_result.entry);
}

obj_t* obj_hash_table_define(obj_hash_table_t* self, const obj_t* key, const obj_t* value) {
    hash_table_entry_t* entry = hash_table_find(&self->hash_table, key);
    if (entry) {
        throw(str_new_cstr("key already exists in hash table"), key, value);
    }
    return *(obj_t**) hash_table_entry_value(&self->hash_table, entry);
}
