#ifndef OBJ_UINT_H
# define OBJ_UINT_H

# include "obj.h"

typedef struct obj_uint_t {
    obj_t base;
} obj_uint_t;

obj_uint_t* obj_uint_new();
void obj_uint_delete(obj_uint_t* self);

bool is_uint(const obj_t* self);
obj_ffi_t* obj_uint_to_ffi(const obj_uint_t* self);
void obj_uint_to_string(const obj_uint_t* self, obj_string_t* str);
obj_t* obj_uint_copy(const obj_uint_t* self);
bool obj_uint_equal(const obj_uint_t* self, const obj_uint_t* other);
size_t obj_uint_hash(const obj_uint_t* self);
obj_t* obj_uint_eval(const obj_uint_t* self, obj_env_t* env);
obj_t* obj_uint_apply(const obj_uint_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_UINT_H
