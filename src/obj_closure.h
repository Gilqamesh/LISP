#ifndef OBJ_CLOSURE_H
# define OBJ_CLOSURE_H

# include "obj.h"

typedef struct obj_closure_t {
    obj_t base;
    obj_t* params;
    obj_t* body;
    obj_env_t* env;
} obj_closure_t;

obj_closure_t* obj_closure_new(obj_t* params, obj_t* body, obj_env_t* env);
void obj_closure_delete(obj_closure_t* self);

bool is_closure(const obj_t* self);
obj_ffi_t* obj_closure_to_ffi(const obj_closure_t* self);
void obj_closure_to_string(const obj_closure_t* self, obj_string_t* str);
obj_closure_t* obj_closure_copy(const obj_closure_t* self);
bool obj_closure_equal(const obj_closure_t* self, const obj_closure_t* other);
bool obj_closure_is_truthy(const obj_closure_t* self);
size_t obj_closure_hash(const obj_closure_t* self);
obj_t* obj_closure_eval(const obj_closure_t* self, obj_env_t* env);
obj_t* obj_closure_apply(const obj_closure_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_CLOSURE_H
