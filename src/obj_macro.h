#ifndef OBJ_MACRO_H
# define OBJ_MACRO_H

# include "obj.h"

typedef struct obj_macro_t {
    obj_t base;
} obj_macro_t;

obj_t* obj_macro_new();
void obj_macro_delete(obj_t* self);

bool is_macro(obj_t* self);
obj_macro_t* obj_as_macro(obj_t* self);
ffi_type* obj_macro_to_ffi(obj_t* self);
void obj_macro_to_string(obj_t* self, obj_t* string);
obj_t* obj_macro_copy(obj_t* self);
bool obj_macro_is_equal(obj_t* self, obj_t* other);
bool obj_macro_is_truthy(obj_t* self);
size_t obj_macro_hash(obj_t* self);
obj_t* obj_macro_eval(obj_t* self, obj_t* env);
obj_t* obj_macro_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_MACRO_H
