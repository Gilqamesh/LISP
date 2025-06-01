#ifndef OBJ_POINTER_H
# define OBJ_POINTER_H

# include "obj.h"

typedef struct obj_pointer_t {
    obj_t base;
} obj_pointer_t;

obj_pointer_t* obj_pointer_new();
void obj_pointer_delete(obj_pointer_t* self);

bool is_pointer(const obj_t* self);
obj_ffi_t* obj_pointer_to_ffi(const obj_pointer_t* self);
void obj_pointer_to_string(const obj_pointer_t* self, obj_string_t* str);
obj_pointer_t* obj_pointer_copy(const obj_pointer_t* self);
bool obj_pointer_equal(const obj_pointer_t* self, const obj_pointer_t* other);
bool obj_pointer_is_truthy(const obj_pointer_t* self);
size_t obj_pointer_hash(const obj_pointer_t* self);
obj_t* obj_pointer_eval(const obj_pointer_t* self, obj_env_t* env);
obj_t* obj_pointer_apply(const obj_pointer_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_POINTER_H
