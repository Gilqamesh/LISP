#ifndef OBJ_R64_H
# define OBJ_R64_H

# include "obj.h"

struct obj_r64_t {
    obj_t base;
    double value;
};

obj_r64_t* obj_r64_new(double value);
void obj_r64_delete(obj_r64_t* self);

bool is_r64(const obj_t* self);
obj_ffi_t* obj_r64_to_ffi(const obj_r64_t* self);
void obj_r64_to_string(const obj_r64_t* self, obj_string_t* other);
obj_r64_t* obj_r64_copy(const obj_r64_t* self);
bool obj_r64_equal(const obj_r64_t* self, const obj_r64_t* other);
bool obj_r64_is_truthy(const obj_r64_t* self);
size_t obj_r64_hash(const obj_r64_t* self);
obj_t* obj_r64_eval(const obj_r64_t* self, obj_env_t* env);
obj_t* obj_r64_apply(const obj_r64_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_R64_H
