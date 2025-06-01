#ifndef OBJ_U16_H
# define OBJ_U16_H

# include "obj.h"

struct obj_u16_t {
    obj_t base;
};

obj_u16_t* obj_u16_new();
void obj_u16_delete(obj_u16_t* self);

bool is_u16(const obj_t* self);
obj_ffi_t* obj_u16_to_ffi(const obj_u16_t* self);
void obj_u16_to_string(const obj_u16_t* self, obj_string_t* other);
obj_u16_t* obj_u16_copy(const obj_u16_t* self);
bool obj_u16_equal(const obj_u16_t* self, const obj_u16_t* other);
bool obj_u16_is_truthy(const obj_u16_t* self);
size_t obj_u16_hash(const obj_u16_t* self);
obj_t* obj_u16_eval(const obj_u16_t* self, obj_env_t* env);
obj_t* obj_u16_apply(const obj_u16_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_U16_H
