#ifndef OBJ_UCHAR_H
# define OBJ_UCHAR_H

# include "obj.h"

typedef struct obj_uchar_t {
    obj_t base;
} obj_uchar_t;

obj_uchar_t* obj_uchar_new();
void obj_uchar_delete(obj_uchar_t* self);

bool is_uchar(const obj_t* self);
obj_ffi_t* obj_uchar_to_ffi(const obj_uchar_t* self);
void obj_uchar_to_string(const obj_uchar_t* self, obj_string_t* str);
obj_t* obj_uchar_copy(const obj_uchar_t* self);
bool obj_uchar_equal(const obj_uchar_t* self, const obj_uchar_t* other);
size_t obj_uchar_hash(const obj_uchar_t* self);
obj_t* obj_uchar_eval(const obj_uchar_t* self, obj_env_t* env);
obj_t* obj_uchar_apply(const obj_uchar_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_UCHAR_H
