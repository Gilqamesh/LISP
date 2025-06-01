#ifndef OBJ_EOF_H
# define OBJ_EOF_H

# include "obj.h"

typedef struct obj_eof_t {
    obj_t base;
} obj_eof_t;

obj_eof_t* obj_eof_new();
void obj_eof_delete(obj_eof_t* self);

bool is_eof(const obj_t* self);
obj_ffi_t* obj_eof_to_ffi(const obj_eof_t* self);
void obj_eof_to_string(const obj_eof_t* self, obj_string_t* str);
obj_eof_t* obj_eof_copy(const obj_eof_t* self);
bool obj_eof_equal(const obj_eof_t* self, const obj_eof_t* other);
bool obj_eof_is_truthy(const obj_eof_t* self);
size_t obj_eof_hash(const obj_eof_t* self);
obj_t* obj_eof_eval(const obj_eof_t* self, obj_env_t* env);
obj_t* obj_eof_apply(const obj_eof_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_EOF_H
