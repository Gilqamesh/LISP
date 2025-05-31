#ifndef OBJ_HASH_TABLE_H
# define OBJ_HASH_TABLE_H

# include "obj.h"

typedef struct obj_hash_table_entry_t {
    bool is_taken;
    size_t index;
    size_t probe_distance;
    const obj_t* key;
    obj_t* value;
} obj_hash_table_entry_t;

typedef struct obj_hash_table_t {
    obj_t base;
    size_t entries_fill;
    size_t entries_size;
    obj_hash_table_entry_t* entries;
} obj_hash_table_t;

obj_hash_table_t* obj_hash_table_new();
void obj_hash_table_delete(obj_hash_table_t* self);

bool is_hash_table(const obj_t* self);
obj_ffi_t* obj_hash_table_to_ffi(const obj_hash_table_t* self);
void obj_hash_table_to_string(const obj_hash_table_t* self, obj_string_t* str);
obj_t* obj_hash_table_copy(const obj_hash_table_t* self);
bool obj_hash_table_equal(const obj_hash_table_t* self, const obj_hash_table_t* other);
size_t obj_hash_table_hash(const obj_hash_table_t* self);
obj_t* obj_hash_table_eval(const obj_hash_table_t* self, obj_env_t* env);
obj_t* obj_hash_table_apply(const obj_hash_table_t* self, obj_array_t* args, obj_env_t* env);

typedef struct obj_hash_table_insert_result_t {
    bool is_new;
    obj_hash_table_entry_t* entry;
} obj_hash_table_insert_result_t;
obj_hash_table_insert_result_t obj_hash_table_insert(obj_hash_table_t* self, const obj_t* key, obj_t* value);
obj_hash_table_entry_t* obj_hash_table_find(const obj_hash_table_t* self, const obj_t* key);
bool obj_hash_table_remove(obj_hash_table_t* self, const obj_t* key);
void obj_hash_table_clear(obj_hash_table_t* self);

size_t obj_hash_table_size(const obj_hash_table_t* self);

obj_hash_table_entry_t* obj_hash_table_first(const obj_hash_table_t* self);
obj_hash_table_entry_t* obj_hash_table_last(const obj_hash_table_t* self);
obj_hash_table_entry_t* obj_hash_table_next(const obj_hash_table_t* self, obj_hash_table_entry_t* entry);
obj_hash_table_entry_t* obj_hash_table_prev(const obj_hash_table_t* self, obj_hash_table_entry_t* entry);

#endif // OBJ_HASH_TABLE_H
