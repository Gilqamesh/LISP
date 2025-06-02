#ifndef OBJ_NIL_H
# define OBJ_NIL_H

# include "obj.h"

typedef struct obj_nil_t {
    obj_t base;
} obj_nil_t;

obj_t* obj_nil_new();
void obj_nil_delete(obj_t* self);

bool is_nil(obj_t* self);
obj_nil_t* obj_as_nil(obj_t* self);
ffi_type* obj_nil_to_ffi(obj_t* self);
void obj_nil_to_string(obj_t* self, obj_t* string);
obj_t* obj_nil_copy(obj_t* self);
bool obj_nil_is_equal(obj_t* self, obj_t* other);
bool obj_nil_is_truthy(obj_t* self);
size_t obj_nil_hash(obj_t* self);
obj_t* obj_nil_eval(obj_t* self, obj_t* env);
obj_t* obj_nil_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_NIL_H
