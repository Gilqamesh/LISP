#ifndef OBJ_REPL_H
# define OBJ_REPL_H

# include "obj.h"

typedef struct obj_repl_t {
    obj_t base;
    obj_t* reader;
    obj_t* env;
} obj_repl_t;

obj_t* obj_repl_new();
void obj_repl_delete(obj_t* self);

bool is_repl(obj_t* self);
obj_repl_t* obj_as_repl(obj_t* self);
ffi_type* obj_repl_to_ffi(obj_t* self);
void obj_repl_to_string(obj_t* self, obj_t* string);
obj_t* obj_repl_copy(obj_t* self);
bool obj_repl_is_equal(obj_t* self, obj_t* other);
bool obj_repl_is_truthy(obj_t* self);
size_t obj_repl_hash(obj_t* self);
obj_t* obj_repl_eval(obj_t* self, obj_t* env);
obj_t* obj_repl_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_REPL_H
