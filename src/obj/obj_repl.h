#ifndef OBJ_REPL_H
# define OBJ_REPL_H

# include "obj.h"

typedef struct obj_repl_t {
    obj_t base;
} obj_repl_t;

obj_repl_t* obj_repl_new();
void obj_repl_delete(obj_repl_t* self);

bool is_repl(const obj_t* self);
obj_ffi_t* obj_repl_to_ffi(const obj_repl_t* self);
void obj_repl_to_string(const obj_repl_t* self, obj_string_t* str);
obj_repl_t* obj_repl_copy(const obj_repl_t* self);
bool obj_repl_equal(const obj_repl_t* self, const obj_repl_t* other);
size_t obj_repl_hash(const obj_repl_t* self);
obj_t* obj_repl_eval(const obj_repl_t* self, obj_env_t* env);
obj_t* obj_repl_apply(const obj_repl_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_REPL_H
