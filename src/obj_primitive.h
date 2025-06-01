#ifndef OBJ_PRIMITIVE_H
# define OBJ_PRIMITIVE_H

# include "obj.h"

typedef obj_t* (*primitive_fn_t)(const obj_primitive_t* self, obj_t* args, obj_env_t* env);

typedef struct obj_primitive_t {
    obj_t base;
    primitive_fn_t primitive_fn;
    bool strict;
} obj_primitive_t;

obj_primitive_t* obj_primitive_new(bool strict, primitive_fn_t primitive_fn);
void obj_primitive_delete(obj_primitive_t* self);

bool is_primitive(const obj_t* self);
obj_ffi_t* obj_primitive_to_ffi(const obj_primitive_t* self);
void obj_primitive_to_string(const obj_primitive_t* self, obj_string_t* str);
obj_primitive_t* obj_primitive_copy(const obj_primitive_t* self);
bool obj_primitive_equal(const obj_primitive_t* self, const obj_primitive_t* other);
bool obj_primitive_is_truthy(const obj_primitive_t* self);
size_t obj_primitive_hash(const obj_primitive_t* self);
obj_t* obj_primitive_eval(const obj_primitive_t* self, obj_env_t* env);
obj_t* obj_primitive_apply(const obj_primitive_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_PRIMITIVE_H
