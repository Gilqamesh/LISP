#ifndef OBJ_SYMBOL_H
# define OBJ_SYMBOL_H

# include "obj.h"

typedef struct obj_symbol_t {
    obj_t base;
    obj_t* symbol;
} obj_symbol_t;

obj_t* obj_symbol_new(obj_t* symbol);
void obj_symbol_delete(obj_t* self);

bool is_symbol(obj_t* self);
obj_symbol_t* obj_as_symbol(obj_t* self);
ffi_type* obj_symbol_to_ffi(obj_t* self);
void obj_symbol_to_string(obj_t* self, obj_t* string);
obj_t* obj_symbol_copy(obj_t* self);
bool obj_symbol_is_equal(obj_t* self, obj_t* other);
bool obj_symbol_is_truthy(obj_t* self);
size_t obj_symbol_hash(obj_t* self);
obj_t* obj_symbol_eval(obj_t* self, obj_t* env);
obj_t* obj_symbol_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_SYMBOL_H
