#ifndef OBJ_I32_H
# define OBJ_I32_H

# include "obj.h"

struct obj_i32_t {
    obj_t base;
    int32_t value;
};

obj_t* obj_i32_new(int32_t value);
void obj_i32_delete(obj_t* self);

bool is_i32(obj_t* self);
obj_i32_t* obj_as_i32(obj_t* self);
ffi_type* obj_i32_to_ffi(obj_t* self);
void obj_i32_to_string(obj_t* self, obj_t* string);
obj_t* obj_i32_copy(obj_t* self);
bool obj_i32_is_equal(obj_t* self, obj_t* other);
bool obj_i32_is_truthy(obj_t* self);
size_t obj_i32_hash(obj_t* self);
obj_t* obj_i32_eval(obj_t* self, obj_t* env);
obj_t* obj_i32_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_I32_H
