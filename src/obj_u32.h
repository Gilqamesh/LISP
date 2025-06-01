#ifndef OBJ_U32_H
# define OBJ_U32_H

# include "obj.h"

struct obj_u32_t {
    obj_t base;
    uint32_t value;
};

obj_u32_t* obj_u32_new(uint32_t value);
void obj_u32_delete(obj_u32_t* self);

bool is_u32(const obj_t* self);
obj_ffi_t* obj_u32_to_ffi(const obj_u32_t* self);
void obj_u32_to_string(const obj_u32_t* self, obj_string_t* other);
obj_u32_t* obj_u32_copy(const obj_u32_t* self);
bool obj_u32_equal(const obj_u32_t* self, const obj_u32_t* other);
bool obj_u32_is_truthy(const obj_u32_t* self);
size_t obj_u32_hash(const obj_u32_t* self);
obj_t* obj_u32_eval(const obj_u32_t* self, obj_env_t* env);
obj_t* obj_u32_apply(const obj_u32_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_U32_H
