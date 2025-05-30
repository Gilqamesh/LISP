#ifndef OBJ_REPL_H
# define OBJ_REPL_H

# include "obj.h"

typedef struct obj_repl_t {
    obj_t base;
} obj_repl_t;

obj_repl_t* obj_repl_new();
void obj_repl_delete(obj_repl_t* self);

bool is_repl(const obj_t* self);
ffi_type* obj_repl_to_ffi_type(const obj_repl_t* self);
void obj_repl_to_string(const obj_repl_t* self, str_t* str);
obj_t* obj_repl_copy(const obj_repl_t* self);
bool obj_repl_equal(const obj_repl_t* self, const obj_repl_t* other);
size_t obj_repl_hash(const obj_repl_t* self);
obj_t* obj_repl_eval(const obj_repl_t* self, obj_hash_table_t* env);
obj_t* obj_repl_apply(const obj_repl_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_REPL_H
