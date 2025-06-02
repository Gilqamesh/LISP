#ifndef OBJ_FFI_H
# define OBJ_FFI_H

# include "obj.h"

typedef struct obj_ffi_t {
    obj_t base;
} obj_ffi_t;

obj_t* obj_ffi_new();
void obj_ffi_delete(obj_t* self);

bool is_ffi(obj_t* self);
obj_ffi_t* obj_as_ffi(obj_t* self);
ffi_type* obj_ffi_to_ffi(obj_t* self);
void obj_ffi_to_string(obj_t* self, obj_t* string);
obj_t* obj_ffi_copy(obj_t* self);
bool obj_ffi_is_equal(obj_t* self, obj_t* other);
bool obj_ffi_is_truthy(obj_t* self);
size_t obj_ffi_hash(obj_t* self);
obj_t* obj_ffi_eval(obj_t* self, obj_t* env);
obj_t* obj_ffi_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_FFI_H
