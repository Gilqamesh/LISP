#ifndef OBJ_USHORT_H
# define OBJ_USHORT_H

# include "obj.h"

typedef struct obj_ushort_t {
    obj_t base;
} obj_ushort_t;

obj_ushort_t* obj_ushort_new();
void obj_ushort_delete(obj_ushort_t* self);

bool is_ushort(const obj_t* self);
ffi_type* obj_ushort_to_ffi_type(const obj_ushort_t* self);
void obj_ushort_to_string(const obj_ushort_t* self, str_t* str);
obj_t* obj_ushort_copy(const obj_ushort_t* self);
bool obj_ushort_equal(const obj_ushort_t* self, const obj_ushort_t* other);
size_t obj_ushort_hash(const obj_ushort_t* self);
obj_t* obj_ushort_eval(const obj_ushort_t* self, obj_hash_table_t* env);
obj_t* obj_ushort_apply(const obj_ushort_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_USHORT_H
