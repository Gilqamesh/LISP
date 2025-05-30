#ifndef OBJ_NIL_H
# define OBJ_NIL_H

# include "obj.h"

typedef struct obj_nil_t {
    obj_t base;
} obj_nil_t;

obj_nil_t* obj_nil_new();
void obj_nil_delete(obj_nil_t* self);

bool is_nil(const obj_t* self);
obj_ffi_t* obj_nil_to_ffi(const obj_nil_t* self);
void obj_nil_to_string(const obj_nil_t* self, obj_string_t* str);
obj_t* obj_nil_copy(const obj_nil_t* self);
bool obj_nil_equal(const obj_nil_t* self, const obj_nil_t* other);
size_t obj_nil_hash(const obj_nil_t* self);
obj_t* obj_nil_eval(const obj_nil_t* self, obj_hash_table_t* env);
obj_t* obj_nil_apply(const obj_nil_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_NIL_H
