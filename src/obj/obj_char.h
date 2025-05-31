#ifndef OBJ_CHAR_H
# define OBJ_CHAR_H

# include "obj.h"

typedef struct obj_char_t {
    obj_t base;
} obj_char_t;

obj_char_t* obj_char_new();
void obj_char_delete(obj_char_t* self);

bool is_char(const obj_t* self);
obj_ffi_t* obj_char_to_ffi(const obj_char_t* self);
void obj_char_to_string(const obj_char_t* self, obj_string_t* str);
obj_char_t* obj_char_copy(const obj_char_t* self);
bool obj_char_equal(const obj_char_t* self, const obj_char_t* other);
size_t obj_char_hash(const obj_char_t* self);
obj_t* obj_char_eval(const obj_char_t* self, obj_env_t* env);
obj_t* obj_char_apply(const obj_char_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_CHAR_H
