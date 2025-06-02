#ifndef OBJ_PRIMITIVE_H
# define OBJ_PRIMITIVE_H

# include "obj.h"

typedef obj_t* (*primitive_fn_t)(obj_t* self, obj_t* args, obj_t* env);

typedef struct obj_primitive_t {
    obj_t base;
    primitive_fn_t primitive_fn;
    bool strict;
} obj_primitive_t;

obj_t* obj_primitive_new(bool strict, primitive_fn_t primitive_fn);
void obj_primitive_delete(obj_t* self);

bool is_primitive(obj_t* self);
obj_primitive_t* obj_as_primitive(obj_t* self);
ffi_type* obj_primitive_to_ffi(obj_t* self);
void obj_primitive_to_string(obj_t* self, obj_t* string);
obj_t* obj_primitive_copy(obj_t* self);
bool obj_primitive_is_equal(obj_t* self, obj_t* other);
bool obj_primitive_is_truthy(obj_t* self);
size_t obj_primitive_hash(obj_t* self);
obj_t* obj_primitive_eval(obj_t* self, obj_t* env);
obj_t* obj_primitive_apply(obj_t* self, obj_t* args, obj_t* env);

obj_t* obj_primitive_if(obj_t* self, obj_t* args, obj_t* env);
obj_t* obj_primitive_lambda(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_PRIMITIVE_H
