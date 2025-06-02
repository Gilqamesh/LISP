#ifndef OBJ_COMBINATION_H
# define OBJ_COMBINATION_H

# include "obj.h"

typedef struct obj_combination_t {
    obj_t base;
    obj_t* unevaluated_op;
    obj_array_t* unevaluated_args;
} obj_combination_t;

obj_t* obj_combination_new(obj_t* unevaluated_op, obj_array_t* unevaluated_args);
void obj_combination_delete(obj_combination_t* self);

bool is_combination(obj_t* self);
ffi_type* obj_combination_to_ffi(obj_combination_t* self);
void obj_combination_to_string(obj_combination_t* self, obj_t* string);
obj_combination_t* obj_combination_copy(obj_combination_t* self);
bool obj_combination_equal(obj_combination_t* self, obj_combination_t* other);
bool obj_combination_is_truthy(obj_combination_t* self);
size_t obj_combination_hash(obj_combination_t* self);
obj_t* obj_combination_eval(obj_combination_t* self, obj_t* env);
obj_t* obj_combination_apply(obj_combination_t* self, obj_t* args, obj_t* env);

#endif // OBJ_COMBINATION_H
