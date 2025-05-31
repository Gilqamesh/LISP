#ifndef OBJ_INT_H
# define OBJ_INT_H

# include "obj.h"

typedef struct obj_int_t {
    obj_t base;
    int integer;
} obj_int_t;

obj_int_t* obj_int_new(int integer);
void obj_int_delete(obj_int_t* self);

bool is_int(const obj_t* self);
obj_ffi_t* obj_int_to_ffi(const obj_int_t* self);
void obj_int_to_string(const obj_int_t* self, obj_string_t* str);
obj_t* obj_int_copy(const obj_int_t* self);
bool obj_int_equal(const obj_int_t* self, const obj_int_t* other);
size_t obj_int_hash(const obj_int_t* self);
obj_t* obj_int_eval(const obj_int_t* self, obj_env_t* env);
obj_t* obj_int_apply(const obj_int_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_INT_H
