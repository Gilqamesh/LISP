#ifndef OBJ_MACRO_H
# define OBJ_MACRO_H

# include "obj.h"

typedef struct obj_macro_t {
    obj_t base;
} obj_macro_t;

obj_macro_t* obj_macro_new();
void obj_macro_delete(obj_macro_t* self);

bool is_macro(const obj_t* self);
obj_ffi_t* obj_macro_to_ffi(const obj_macro_t* self);
void obj_macro_to_string(const obj_macro_t* self, obj_string_t* str);
obj_t* obj_macro_copy(const obj_macro_t* self);
bool obj_macro_equal(const obj_macro_t* self, const obj_macro_t* other);
size_t obj_macro_hash(const obj_macro_t* self);
obj_t* obj_macro_eval(const obj_macro_t* self, obj_env_t* env);
obj_t* obj_macro_apply(const obj_macro_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_MACRO_H
