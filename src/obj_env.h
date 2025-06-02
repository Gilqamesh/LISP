#ifndef OBJ_ENV_H
# define OBJ_ENV_H

# include "obj.h"

struct obj_env_t {
    obj_t base;
    obj_t* hash_table;
    obj_t* parent;
};

obj_t* obj_env_new();
void obj_env_delete(obj_t* self);

bool is_env(obj_t* self);
obj_env_t* obj_as_env(obj_t* self);
ffi_type* obj_env_to_ffi(obj_t* self);
void obj_env_to_string(obj_t* self, obj_t* string);
obj_t* obj_env_copy(obj_t* self);
bool obj_env_is_equal(obj_t* self, obj_t* other);
bool obj_env_is_truthy(obj_t* self);
size_t obj_env_hash(obj_t* self);
obj_t* obj_env_eval(obj_t* self, obj_t* env);
obj_t* obj_env_apply(obj_t* self, obj_t* args, obj_t* env);

obj_t* obj_env_set_parent(obj_t* self, obj_t* parent);
obj_t* obj_env_get_parent(obj_t* self);

obj_t* obj_env_get(obj_t* self, obj_t* key);
obj_t* obj_env_set(obj_t* self, obj_t* key, obj_t* value);
obj_t* obj_env_define(obj_t* self, obj_t* key, obj_t* value);

obj_t* obj_env_extend(obj_t* self, obj_t* params, obj_t* args);

#endif // OBJ_ENV_H
