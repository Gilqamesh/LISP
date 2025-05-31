#ifndef OBJ_LISP_TYPE_H
# define OBJ_LISP_TYPE_H

# include "obj.h"

typedef struct obj_lisp_type_t {
    obj_t base;
} obj_lisp_type_t;

obj_lisp_type_t* obj_lisp_type_new();
void obj_lisp_type_delete(obj_lisp_type_t* self);

bool is_lisp_type(const obj_t* self);
obj_ffi_t* obj_lisp_type_to_ffi(const obj_lisp_type_t* self);
void obj_lisp_type_to_string(const obj_lisp_type_t* self, obj_string_t* str);
obj_lisp_type_t* obj_lisp_type_copy(const obj_lisp_type_t* self);
bool obj_lisp_type_equal(const obj_lisp_type_t* self, const obj_lisp_type_t* other);
size_t obj_lisp_type_hash(const obj_lisp_type_t* self);
obj_t* obj_lisp_type_eval(const obj_lisp_type_t* self, obj_env_t* env);
obj_t* obj_lisp_type_apply(const obj_lisp_type_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_LISP_TYPE_H
