#ifndef OBJ_FFI_H
# define OBJ_FFI_H

# include "obj.h"

# include "ffi.h"

typedef struct obj_ffi_t {
    obj_t base;
} obj_ffi_t;

obj_ffi_t* obj_ffi_new();
void obj_ffi_delete(obj_ffi_t* self);

bool is_ffi(const obj_t* self);
obj_ffi_t* obj_ffi_to_ffi(const obj_ffi_t* self);
void obj_ffi_to_string(const obj_ffi_t* self, obj_string_t* str);
obj_t* obj_ffi_copy(const obj_ffi_t* self);
bool obj_ffi_equal(const obj_ffi_t* self, const obj_ffi_t* other);
size_t obj_ffi_hash(const obj_ffi_t* self);
obj_t* obj_ffi_eval(const obj_ffi_t* self, obj_env_t* env);
obj_t* obj_ffi_apply(const obj_ffi_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_FFI_H
