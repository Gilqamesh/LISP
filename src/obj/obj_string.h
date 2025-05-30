#ifndef OBJ_STRING_H
# define OBJ_STRING_H

# include "obj.h"

typedef struct obj_string_t {
    obj_t base;
    str_t str;
} obj_string_t;

obj_string_t* obj_string_new(str_t str);
void obj_string_delete(obj_string_t* self);

bool is_string(const obj_t* self);
ffi_type* obj_string_to_ffi_type(const obj_string_t* self);
void obj_string_to_string(const obj_string_t* self, str_t* str);
obj_t* obj_string_copy(const obj_string_t* self);
bool obj_string_equal(const obj_string_t* self, const obj_string_t* other);
size_t obj_string_hash(const obj_string_t* self);
obj_t* obj_string_eval(const obj_string_t* self, obj_hash_table_t* env);
obj_t* obj_string_apply(const obj_string_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_STRING_H
