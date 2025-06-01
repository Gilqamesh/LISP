#ifndef OBJ_I16_H
# define OBJ_I16_H

# include "obj.h"

struct obj_i16_t {
    obj_t base;
    int16_t value;
};

obj_i16_t* obj_i16_new(int16_t value);
void obj_i16_delete(obj_i16_t* self);

bool is_i16(const obj_t* self);
obj_ffi_t* obj_i16_to_ffi(const obj_i16_t* self);
void obj_i16_to_string(const obj_i16_t* self, obj_string_t* other);
obj_i16_t* obj_i16_copy(const obj_i16_t* self);
bool obj_i16_equal(const obj_i16_t* self, const obj_i16_t* other);
bool obj_i16_is_truthy(const obj_i16_t* self);
size_t obj_i16_hash(const obj_i16_t* self);
obj_t* obj_i16_eval(const obj_i16_t* self, obj_env_t* env);
obj_t* obj_i16_apply(const obj_i16_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_I16_H
