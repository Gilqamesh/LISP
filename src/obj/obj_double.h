#ifndef OBJ_DOUBLE_H
# define OBJ_DOUBLE_H

# include "obj.h"

typedef struct obj_double_t {
    obj_t base;
} obj_double_t;

obj_double_t* obj_double_new();
void obj_double_delete(obj_double_t* self);

bool is_double(const obj_t* self);
obj_ffi_t* obj_double_to_ffi(const obj_double_t* self);
void obj_double_to_string(const obj_double_t* self, obj_string_t* str);
obj_t* obj_double_copy(const obj_double_t* self);
bool obj_double_equal(const obj_double_t* self, const obj_double_t* other);
size_t obj_double_hash(const obj_double_t* self);
obj_t* obj_double_eval(const obj_double_t* self, obj_env_t* env);
obj_t* obj_double_apply(const obj_double_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_DOUBLE_H
