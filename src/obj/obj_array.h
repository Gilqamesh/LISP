#ifndef OBJ_ARRAY_H
# define OBJ_ARRAY_H

# include "obj.h"

typedef struct obj_array_t {
    obj_t base;
    size_t objs_capacity;
    size_t objs_fill;
    obj_t** objs;
} obj_array_t;

obj_array_t* obj_array_new();
void obj_array_delete(obj_array_t* self);

bool is_array(const obj_t* self);
obj_ffi_t* obj_array_to_ffi(const obj_array_t* self);
void obj_array_to_string(const obj_array_t* self, obj_string_t* str);
obj_array_t* obj_array_copy(const obj_array_t* self);
bool obj_array_equal(const obj_array_t* self, const obj_array_t* other);
size_t obj_array_hash(const obj_array_t* self);
obj_t* obj_array_eval(const obj_array_t* self, obj_env_t* env);
obj_t* obj_array_apply(const obj_array_t* self, obj_array_t* args, obj_env_t* env);

obj_t* obj_array_push(obj_array_t* self, obj_t* obj);
void obj_array_push_array(obj_array_t* self, const obj_array_t* other);
obj_t* obj_array_pop(obj_array_t* self);
void obj_array_clear(obj_array_t* self);

size_t obj_array_size(const obj_array_t* self);
obj_t* obj_array_read(const obj_array_t* self, size_t index);
obj_t* obj_array_write(obj_array_t* self, size_t index, obj_t* obj);

#endif // OBJ_ARRAY_H
