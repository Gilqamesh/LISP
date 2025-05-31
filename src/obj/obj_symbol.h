#ifndef OBJ_SYMBOL_H
# define OBJ_SYMBOL_H

# include "obj.h"

typedef struct obj_symbol_t {
    obj_t base;
} obj_symbol_t;

obj_symbol_t* obj_symbol_new();
void obj_symbol_delete(obj_symbol_t* self);

bool is_symbol(const obj_t* self);
obj_ffi_t* obj_symbol_to_ffi(const obj_symbol_t* self);
void obj_symbol_to_string(const obj_symbol_t* self, obj_string_t* str);
obj_t* obj_symbol_copy(const obj_symbol_t* self);
bool obj_symbol_equal(const obj_symbol_t* self, const obj_symbol_t* other);
size_t obj_symbol_hash(const obj_symbol_t* self);
obj_t* obj_symbol_eval(const obj_symbol_t* self, obj_env_t* env);
obj_t* obj_symbol_apply(const obj_symbol_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_SYMBOL_H
