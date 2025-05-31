#ifndef OBJ_VOID_H
# define OBJ_VOID_H

# include "obj.h"

typedef struct obj_void_t {
    obj_t base;
} obj_void_t;

obj_void_t* obj_void_new();
void obj_void_delete(obj_void_t* self);

bool is_void(const obj_t* self);
obj_ffi_t* obj_void_to_ffi(const obj_void_t* self);
void obj_void_to_string(const obj_void_t* self, obj_string_t* str);
obj_void_t* obj_void_copy(const obj_void_t* self);
bool obj_void_equal(const obj_void_t* self, const obj_void_t* other);
size_t obj_void_hash(const obj_void_t* self);
obj_t* obj_void_eval(const obj_void_t* self, obj_env_t* env);
obj_t* obj_void_apply(const obj_void_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_VOID_H
