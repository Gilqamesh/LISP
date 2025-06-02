#ifndef OBJ_VOID_H
# define OBJ_VOID_H

# include "obj.h"

typedef struct obj_void_t {
    obj_t base;
} obj_void_t;

obj_t* obj_void_new();
void obj_void_delete(obj_t* self);

bool is_void(obj_t* self);
obj_void_t* obj_as_void(obj_t* self);
ffi_type* obj_void_to_ffi(obj_t* self);
void obj_void_to_string(obj_t* self, obj_t* string);
obj_t* obj_void_copy(obj_t* self);
bool obj_void_is_equal(obj_t* self, obj_t* other);
bool obj_void_is_truthy(obj_t* self);
size_t obj_void_hash(obj_t* self);
obj_t* obj_void_eval(obj_t* self, obj_t* env);
obj_t* obj_void_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_VOID_H
