#ifndef OBJ_LONG_H
# define OBJ_LONG_H

# include "obj.h"

typedef struct obj_long_t {
    obj_t base;
} obj_long_t;

obj_long_t* obj_long_new();
void obj_long_delete(obj_long_t* self);

bool is_long(const obj_t* self);
obj_ffi_t* obj_long_to_ffi(const obj_long_t* self);
void obj_long_to_string(const obj_long_t* self, obj_string_t* str);
obj_t* obj_long_copy(const obj_long_t* self);
bool obj_long_equal(const obj_long_t* self, const obj_long_t* other);
size_t obj_long_hash(const obj_long_t* self);
obj_t* obj_long_eval(const obj_long_t* self, obj_hash_table_t* env);
obj_t* obj_long_apply(const obj_long_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_LONG_H
