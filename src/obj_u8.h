#ifndef OBJ_U8_H
# define OBJ_U8_H

# include "obj.h"

struct obj_u8_t {
    obj_t base;
    uint8_t value;
};

obj_u8_t* obj_u8_new(uint8_t value);
void obj_u8_delete(obj_u8_t* self);

bool is_u8(const obj_t* self);
obj_ffi_t* obj_u8_to_ffi(const obj_u8_t* self);
void obj_u8_to_string(const obj_u8_t* self, obj_string_t* other);
obj_u8_t* obj_u8_copy(const obj_u8_t* self);
bool obj_u8_equal(const obj_u8_t* self, const obj_u8_t* other);
bool obj_u8_is_truthy(const obj_u8_t* self);
size_t obj_u8_hash(const obj_u8_t* self);
obj_t* obj_u8_eval(const obj_u8_t* self, obj_env_t* env);
obj_t* obj_u8_apply(const obj_u8_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_U8_H
