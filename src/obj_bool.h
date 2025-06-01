#ifndef OBJ_BOOL_H
# define OBJ_BOOL_H

# include "obj.h"

typedef struct obj_bool_t {
    obj_t base;
} obj_bool_t;

obj_bool_t* obj_bool_new();
void obj_bool_delete(obj_bool_t* self);

bool is_bool(const obj_t* self);
obj_ffi_t* obj_bool_to_ffi(const obj_bool_t* self);
void obj_bool_to_string(const obj_bool_t* self, obj_string_t* str);
obj_bool_t* obj_bool_copy(const obj_bool_t* self);
bool obj_bool_equal(const obj_bool_t* self, const obj_bool_t* other);
bool obj_bool_is_truthy(const obj_bool_t* self);
size_t obj_bool_hash(const obj_bool_t* self);
obj_t* obj_bool_eval(const obj_bool_t* self, obj_env_t* env);
obj_t* obj_bool_apply(const obj_bool_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_BOOL_H
