#ifndef OBJ_POINTER_H
# define OBJ_POINTER_H

# include "obj.h"

typedef struct obj_pointer_t {
    obj_t base;
    void* ptr;
} obj_pointer_t;

obj_t* obj_pointer_new(void* ptr);
void obj_pointer_delete(obj_t* self);

bool is_pointer(obj_t* self);
obj_pointer_t* obj_as_pointer(obj_t* self);
ffi_type* obj_pointer_to_ffi(obj_t* self);
void obj_pointer_to_string(obj_t* self, obj_t* string);
obj_t* obj_pointer_copy(obj_t* self);
bool obj_pointer_is_equal(obj_t* self, obj_t* other);
bool obj_pointer_is_truthy(obj_t* self);
size_t obj_pointer_hash(obj_t* self);
obj_t* obj_pointer_eval(obj_t* self, obj_t* env);
obj_t* obj_pointer_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_POINTER_H
