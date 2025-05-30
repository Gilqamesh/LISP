#ifndef OBJ_ULONG_H
# define OBJ_ULONG_H

# include "obj.h"

typedef struct obj_ulong_t {
    obj_t base;
} obj_ulong_t;

obj_ulong_t* obj_ulong_new();
void obj_ulong_delete(obj_ulong_t* self);

bool is_ulong(const obj_t* self);
obj_ffi_t* obj_ulong_to_ffi(const obj_ulong_t* self);
void obj_ulong_to_string(const obj_ulong_t* self, obj_string_t* str);
obj_t* obj_ulong_copy(const obj_ulong_t* self);
bool obj_ulong_equal(const obj_ulong_t* self, const obj_ulong_t* other);
size_t obj_ulong_hash(const obj_ulong_t* self);
obj_t* obj_ulong_eval(const obj_ulong_t* self, obj_hash_table_t* env);
obj_t* obj_ulong_apply(const obj_ulong_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_ULONG_H
