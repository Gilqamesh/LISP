#ifndef OBJ_HASH_TABLE_H
# define OBJ_HASH_TABLE_H

# include "obj.h"

typedef struct obj_hash_table_t {
    obj_t base;
    hash_table_t hash_table;
    obj_hash_table_t* parent;
} obj_hash_table_t;

obj_hash_table_t* obj_hash_table_new();
void obj_hash_table_delete(obj_hash_table_t* self);

bool is_hash_table(const obj_t* self);
ffi_type* obj_hash_table_to_ffi_type(const obj_hash_table_t* self);
void obj_hash_table_to_string(const obj_hash_table_t* self, str_t* str);
obj_t* obj_hash_table_copy(const obj_hash_table_t* self);
bool obj_hash_table_equal(const obj_hash_table_t* self, const obj_hash_table_t* other);
size_t obj_hash_table_hash(const obj_hash_table_t* self);
obj_t* obj_hash_table_eval(const obj_hash_table_t* self, obj_hash_table_t* env);
obj_t* obj_hash_table_apply(const obj_hash_table_t* self, obj_array_t* args, obj_hash_table_t* env);

obj_t* obj_hash_table_get(const obj_hash_table_t* self, const obj_t* key);
obj_t* obj_hash_table_set(obj_hash_table_t* self, const obj_t* key, const obj_t* value);
obj_t* obj_hash_table_define(obj_hash_table_t* self, const obj_t* key, const obj_t* value);

#endif // OBJ_HASH_TABLE_H
