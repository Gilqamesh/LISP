#ifndef OBJ_ENV_H
# define OBJ_ENV_H

# include "obj.h"

typedef struct obj_env_t {
    obj_t base;
    obj_hash_table_t* hash_table;
    obj_env_t* parent;
} obj_env_t;

obj_env_t* obj_env_new();
void obj_env_delete(obj_env_t* self);

bool is_env(const obj_t* self);
obj_ffi_t* obj_env_to_ffi(const obj_env_t* self);
void obj_env_to_string(const obj_env_t* self, obj_string_t* str);
obj_env_t* obj_env_copy(const obj_env_t* self);
bool obj_env_equal(const obj_env_t* self, const obj_env_t* other);
size_t obj_env_hash(const obj_env_t* self);
obj_t* obj_env_eval(const obj_env_t* self, obj_env_t* env);
obj_t* obj_env_apply(const obj_env_t* self, obj_array_t* args, obj_env_t* env);

obj_t* obj_env_get(const obj_env_t* self, const obj_t* key);
obj_t* obj_env_set(obj_env_t* self, const obj_t* key, obj_t* value);
obj_t* obj_env_define(obj_env_t* self, const obj_t* key, obj_t* value);

#endif // OBJ_ENV_H
