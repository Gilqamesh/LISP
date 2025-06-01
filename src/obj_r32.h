#ifndef OBJ_R32_H
# define OBJ_R32_H

# include "obj.h"

struct obj_r32_t {
    obj_t base;
    float value;
};

obj_r32_t* obj_r32_new(float value);
void obj_r32_delete(obj_r32_t* self);

bool is_r32(const obj_t* self);
obj_ffi_t* obj_r32_to_ffi(const obj_r32_t* self);
void obj_r32_to_string(const obj_r32_t* self, obj_string_t* other);
obj_r32_t* obj_r32_copy(const obj_r32_t* self);
bool obj_r32_equal(const obj_r32_t* self, const obj_r32_t* other);
bool obj_r32_is_truthy(const obj_r32_t* self);
size_t obj_r32_hash(const obj_r32_t* self);
obj_t* obj_r32_eval(const obj_r32_t* self, obj_env_t* env);
obj_t* obj_r32_apply(const obj_r32_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_R32_H
