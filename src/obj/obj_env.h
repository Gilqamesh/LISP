#ifndef OBJ_ENV_H
# define OBJ_ENV_H

# include "obj.h"

typedef struct obj_env_t {
    obj_t base;
} obj_env_t;

obj_env_t* obj_env_new();
void obj_env_delete(obj_env_t* self);

bool is_env(const obj_t* self);
ffi_type* obj_env_to_ffi_type(const obj_env_t* self);
void obj_env_to_string(const obj_env_t* self, str_t* str);
obj_t* obj_env_copy(const obj_env_t* self);
bool obj_env_equal(const obj_env_t* self, const obj_env_t* other);
size_t obj_env_hash(const obj_env_t* self);
obj_t* obj_env_eval(const obj_env_t* self, obj_hash_table_t* env);
obj_t* obj_env_apply(const obj_env_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_ENV_H
