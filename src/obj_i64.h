#ifndef OBJ_I64_H
# define OBJ_I64_H

# include "obj.h"

struct obj_i64_t {
    obj_t base;
    int64_t value;
};

obj_i64_t* obj_i64_new(int64_t value);
void obj_i64_delete(obj_i64_t* self);

bool is_i64(const obj_t* self);
obj_ffi_t* obj_i64_to_ffi(const obj_i64_t* self);
void obj_i64_to_string(const obj_i64_t* self, obj_string_t* other);
obj_i64_t* obj_i64_copy(const obj_i64_t* self);
bool obj_i64_equal(const obj_i64_t* self, const obj_i64_t* other);
bool obj_i64_is_truthy(const obj_i64_t* self);
size_t obj_i64_hash(const obj_i64_t* self);
obj_t* obj_i64_eval(const obj_i64_t* self, obj_env_t* env);
obj_t* obj_i64_apply(const obj_i64_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_I64_H
