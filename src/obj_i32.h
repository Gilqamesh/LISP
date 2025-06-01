#ifndef OBJ_I32_H
# define OBJ_I32_H

# include "obj.h"

struct obj_i32_t {
    obj_t base;
    int32_t value;
};

obj_i32_t* obj_i32_new(int32_t value);
void obj_i32_delete(obj_i32_t* self);

bool is_i32(const obj_t* self);
obj_ffi_t* obj_i32_to_ffi(const obj_i32_t* self);
void obj_i32_to_string(const obj_i32_t* self, obj_string_t* other);
obj_i32_t* obj_i32_copy(const obj_i32_t* self);
bool obj_i32_equal(const obj_i32_t* self, const obj_i32_t* other);
bool obj_i32_is_truthy(const obj_i32_t* self);
size_t obj_i32_hash(const obj_i32_t* self);
obj_t* obj_i32_eval(const obj_i32_t* self, obj_env_t* env);
obj_t* obj_i32_apply(const obj_i32_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_I32_H
