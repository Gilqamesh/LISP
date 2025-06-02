#ifndef OBJ_LISP_TYPE_H
# define OBJ_LISP_TYPE_H

# include "obj.h"

struct obj_lisp_type_t {
    obj_t base;
};

obj_t* obj_lisp_type_new();
void obj_lisp_type_delete(obj_t* self);

bool is_lisp_type(obj_t* self);
obj_lisp_type_t* obj_as_lisp_type(obj_t* self);
ffi_type* obj_lisp_type_to_ffi(obj_t* self);
void obj_lisp_type_to_string(obj_t* self, obj_t* string);
obj_t* obj_lisp_type_copy(obj_t* self);
bool obj_lisp_type_is_equal(obj_t* self, obj_t* other);
bool obj_lisp_type_is_truthy(obj_t* self);
size_t obj_lisp_type_hash(obj_t* self);
obj_t* obj_lisp_type_eval(obj_t* self, obj_t* env);
obj_t* obj_lisp_type_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_LISP_TYPE_H
