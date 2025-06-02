#ifndef OBJ_BOOL_H
# define OBJ_BOOL_H

# include "obj.h"

typedef struct obj_bool_t {
    obj_t base;
    bool value;
} obj_bool_t;

obj_t* obj_bool_new(bool value);
void obj_bool_delete(obj_t* self);

bool is_bool(obj_t* self);
obj_bool_t* obj_as_bool(obj_t* self);
ffi_type* obj_bool_to_ffi(obj_t* self);
void obj_bool_to_string(obj_t* self, obj_t* string);
obj_t* obj_bool_copy(obj_t* self);
bool obj_bool_is_equal(obj_t* self, obj_t* other);
bool obj_bool_is_truthy(obj_t* self);
size_t obj_bool_hash(obj_t* self);
obj_t* obj_bool_eval(obj_t* self, obj_t* env);
obj_t* obj_bool_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_BOOL_H
