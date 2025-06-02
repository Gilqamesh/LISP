#ifndef OBJ_CLOSURE_H
# define OBJ_CLOSURE_H

# include "obj.h"

typedef struct obj_closure_t {
    obj_t base;
    obj_t* params;
    obj_t* body;
    obj_t* env;
} obj_closure_t;

obj_t* obj_closure_new(obj_t* params, obj_t* body, obj_t* env);
void obj_closure_delete(obj_t* self);

bool is_closure(obj_t* self);
obj_closure_t* obj_as_closure(obj_t* self);
ffi_type* obj_closure_to_ffi(obj_t* self);
void obj_closure_to_string(obj_t* self, obj_t* string);
obj_t* obj_closure_copy(obj_t* self);
bool obj_closure_is_equal(obj_t* self, obj_t* other);
bool obj_closure_is_truthy(obj_t* self);
size_t obj_closure_hash(obj_t* self);
obj_t* obj_closure_eval(obj_t* self, obj_t* env);
obj_t* obj_closure_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_CLOSURE_H
