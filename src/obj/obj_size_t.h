#ifndef OBJ_SIZE_T_H
# define OBJ_SIZE_T_H

# include "obj.h"

typedef struct obj_size_t_t {
    obj_t base;
    size_t value;
} obj_size_t_t;

obj_size_t_t* obj_size_t_new(size_t value);
void obj_size_t_delete(obj_size_t_t* self);

bool is_size_t(const obj_t* self);
obj_ffi_t* obj_size_t_to_ffi(const obj_size_t_t* self);
void obj_size_t_to_string(const obj_size_t_t* self, obj_string_t* other);
obj_t* obj_size_t_copy(const obj_size_t_t* self);
bool obj_size_t_equal(const obj_size_t_t* self, const obj_size_t_t* other);
size_t obj_size_t_hash(const obj_size_t_t* self);
obj_t* obj_size_t_eval(const obj_size_t_t* self, obj_hash_table_t* env);
obj_t* obj_size_t_apply(const obj_size_t_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_SIZE_T_H
