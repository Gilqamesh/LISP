#ifndef OBJ_U64_H
# define OBJ_U64_H

# include "obj.h"

struct obj_u64_t {
    obj_t base;
    uint64_t value;
};

obj_u64_t* obj_u64_new(uint64_t value);
void obj_u64_delete(obj_u64_t* self);

bool is_u64(const obj_t* self);
obj_ffi_t* obj_u64_to_ffi(const obj_u64_t* self);
void obj_u64_to_string(const obj_u64_t* self, obj_string_t* other);
obj_u64_t* obj_u64_copy(const obj_u64_t* self);
bool obj_u64_equal(const obj_u64_t* self, const obj_u64_t* other);
bool obj_u64_is_truthy(const obj_u64_t* self);
size_t obj_u64_hash(const obj_u64_t* self);
obj_t* obj_u64_eval(const obj_u64_t* self, obj_env_t* env);
obj_t* obj_u64_apply(const obj_u64_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_U64_H
