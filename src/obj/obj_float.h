#ifndef OBJ_FLOAT_H
# define OBJ_FLOAT_H

# include "obj.h"

typedef struct obj_float_t {
    obj_t base;
} obj_float_t;

obj_float_t* obj_float_new();
void obj_float_delete(obj_float_t* self);

bool is_float(const obj_t* self);
ffi_type* obj_float_to_ffi_type(const obj_float_t* self);
void obj_float_to_string(const obj_float_t* self, str_t* str);
obj_t* obj_float_copy(const obj_float_t* self);
bool obj_float_equal(const obj_float_t* self, const obj_float_t* other);
size_t obj_float_hash(const obj_float_t* self);
obj_t* obj_float_eval(const obj_float_t* self, obj_hash_table_t* env);
obj_t* obj_float_apply(const obj_float_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_FLOAT_H
