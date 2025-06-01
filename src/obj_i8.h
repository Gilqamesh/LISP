#ifndef OBJ_I8_H
# define OBJ_I8_H

# include "obj.h"

struct obj_i8_t {
    obj_t base;
    int8_t value;
};

obj_i8_t* obj_i8_new(int8_t value);
void obj_i8_delete(obj_i8_t* self);

bool is_i8(const obj_t* self);
obj_ffi_t* obj_i8_to_ffi(const obj_i8_t* self);
void obj_i8_to_string(const obj_i8_t* self, obj_string_t* other);
obj_i8_t* obj_i8_copy(const obj_i8_t* self);
bool obj_i8_equal(const obj_i8_t* self, const obj_i8_t* other);
bool obj_i8_is_truthy(const obj_i8_t* self);
size_t obj_i8_hash(const obj_i8_t* self);
obj_t* obj_i8_eval(const obj_i8_t* self, obj_env_t* env);
obj_t* obj_i8_apply(const obj_i8_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_I8_H
