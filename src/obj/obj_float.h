#ifndef OBJ_FLOAT_H
# define OBJ_FLOAT_H

# include "obj.h"

typedef struct obj_float_t {
    obj_t base;
} obj_float_t;

obj_float_t* obj_float_new();
void obj_float_delete(obj_float_t* self);

bool is_float(const obj_t* self);
obj_ffi_t* obj_float_to_ffi(const obj_float_t* self);
void obj_float_to_string(const obj_float_t* self, obj_string_t* str);
obj_t* obj_float_copy(const obj_float_t* self);
bool obj_float_equal(const obj_float_t* self, const obj_float_t* other);
size_t obj_float_hash(const obj_float_t* self);
obj_t* obj_float_eval(const obj_float_t* self, obj_env_t* env);
obj_t* obj_float_apply(const obj_float_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_FLOAT_H
