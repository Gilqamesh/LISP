#ifndef OBJ_R64_H
# define OBJ_R64_H

# include "obj.h"

struct obj_r64_t {
    obj_t base;
    double value;
};

obj_t* obj_r64_new(double value);
void obj_r64_delete(obj_t* self);

bool is_r64(obj_t* self);
obj_r64_t* obj_as_r64(obj_t* self);
ffi_type* obj_r64_to_ffi(obj_t* self);
void obj_r64_to_string(obj_t* self, obj_t* string);
obj_t* obj_r64_copy(obj_t* self);
bool obj_r64_is_equal(obj_t* self, obj_t* other);
bool obj_r64_is_truthy(obj_t* self);
size_t obj_r64_hash(obj_t* self);
obj_t* obj_r64_eval(obj_t* self, obj_t* env);
obj_t* obj_r64_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_R64_H
