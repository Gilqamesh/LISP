#ifndef OBJ_COMBINATION_H
# define OBJ_COMBINATION_H

# include "obj.h"

typedef struct obj_combination_t {
    obj_t base;
    obj_t* unevaluated_op;
    obj_array_t* unevaluated_args;
} obj_combination_t;

obj_combination_t* obj_combination_new(obj_t* unevaluated_op, obj_array_t* unevaluated_args);
void obj_combination_delete(obj_combination_t* self);

bool is_combination(const obj_t* self);
obj_ffi_t* obj_combination_to_ffi(const obj_combination_t* self);
void obj_combination_to_string(const obj_combination_t* self, obj_string_t* other);
obj_combination_t* obj_combination_copy(const obj_combination_t* self);
bool obj_combination_equal(const obj_combination_t* self, const obj_combination_t* other);
size_t obj_combination_hash(const obj_combination_t* self);
obj_t* obj_combination_eval(const obj_combination_t* self, obj_env_t* env);
obj_t* obj_combination_apply(const obj_combination_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_COMBINATION_H
