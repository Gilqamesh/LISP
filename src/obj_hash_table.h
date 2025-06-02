#ifndef OBJ_HASH_TABLE_H
# define OBJ_HASH_TABLE_H

# include "obj.h"

typedef struct hash_table_entry_t {
    bool is_taken;
    size_t index;
    size_t probe_distance;
    obj_t* key;
    obj_t* value;
} hash_table_entry_t;

struct obj_hash_table_t {
    obj_t base;
    size_t entries_fill;
    size_t entries_size;
    hash_table_entry_t* entries;
};

obj_t* obj_hash_table_new();
void obj_hash_table_delete(obj_t* self);

bool is_hash_table(obj_t* self);
obj_hash_table_t* obj_as_hash_table(obj_t* self);
ffi_type* obj_hash_table_to_ffi(obj_t* self);
void obj_hash_table_to_string(obj_t* self, obj_t* string);
obj_t* obj_hash_table_copy(obj_t* self);
bool obj_hash_table_is_equal(obj_t* self, obj_t* other);
bool obj_hash_table_is_truthy(obj_t* self);
size_t obj_hash_table_hash(obj_t* self);
obj_t* obj_hash_table_eval(obj_t* self, obj_t* env);
obj_t* obj_hash_table_apply(obj_t* self, obj_t* args, obj_t* env);

typedef struct hash_table_insert_result_t {
    bool is_new;
    hash_table_entry_t* entry;
} hash_table_insert_result_t;
hash_table_insert_result_t obj_hash_table_insert(obj_t* self, obj_t* key, obj_t* value);
hash_table_entry_t* obj_hash_table_find(obj_t* self, obj_t* key);
bool obj_hash_table_remove(obj_t* self, obj_t* key);
void obj_hash_table_clear(obj_t* self);

size_t obj_hash_table_size(obj_t* self);

hash_table_entry_t* obj_hash_table_first(obj_t* self);
hash_table_entry_t* obj_hash_table_last(obj_t* self);
hash_table_entry_t* obj_hash_table_next(obj_t* self, hash_table_entry_t* entry);
hash_table_entry_t* obj_hash_table_prev(obj_t* self, hash_table_entry_t* entry);

#endif // OBJ_HASH_TABLE_H
