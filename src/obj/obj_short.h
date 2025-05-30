#ifndef OBJ_SHORT_H
# define OBJ_SHORT_H

# include "obj.h"

typedef struct obj_short_t {
    obj_t base;
} obj_short_t;

obj_short_t* obj_short_new();
void obj_short_delete(obj_short_t* self);

bool is_short(const obj_t* self);
obj_ffi_t* obj_short_to_ffi(const obj_short_t* self);
void obj_short_to_string(const obj_short_t* self, obj_string_t* str);
obj_t* obj_short_copy(const obj_short_t* self);
bool obj_short_equal(const obj_short_t* self, const obj_short_t* other);
size_t obj_short_hash(const obj_short_t* self);
obj_t* obj_short_eval(const obj_short_t* self, obj_hash_table_t* env);
obj_t* obj_short_apply(const obj_short_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_SHORT_H
