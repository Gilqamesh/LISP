#ifndef OBJ_EOF_H
# define OBJ_EOF_H

# include "obj.h"

typedef struct obj_eof_t {
    obj_t base;
} obj_eof_t;

obj_t* obj_eof_new();
void obj_eof_delete(obj_t* self);

bool is_eof(obj_t* self);
obj_eof_t* obj_as_eof(obj_t* self);
ffi_type* obj_eof_to_ffi(obj_t* self);
void obj_eof_to_string(obj_t* self, obj_t* string);
obj_t* obj_eof_copy(obj_t* self);
bool obj_eof_is_equal(obj_t* self, obj_t* other);
bool obj_eof_is_truthy(obj_t* self);
size_t obj_eof_hash(obj_t* self);
obj_t* obj_eof_eval(obj_t* self, obj_t* env);
obj_t* obj_eof_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_EOF_H
