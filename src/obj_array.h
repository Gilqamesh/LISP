#ifndef OBJ_ARRAY_H
# define OBJ_ARRAY_H

# include "obj.h"

typedef struct obj_array_t {
    obj_t base;
    size_t objs_capacity;
    size_t objs_fill;
    obj_t** objs;
} obj_array_t;

obj_t* obj_array_new();
void obj_array_delete(obj_t* self);

bool is_array(obj_t* self);
obj_array_t* obj_as_array(obj_t* self);
ffi_type* obj_array_to_ffi(obj_t* self);
void obj_array_to_string(obj_t* self, obj_t* string);
obj_t* obj_array_copy(obj_t* self);
bool obj_array_is_equal(obj_t* self, obj_t* other);
bool obj_array_is_truthy(obj_t* self);
size_t obj_array_hash(obj_t* self);
obj_t* obj_array_eval(obj_t* self, obj_t* env);
obj_t* obj_array_apply(obj_t* self, obj_t* args, obj_t* env);

obj_t* obj_array_push(obj_t* self, obj_t* obj);
void obj_array_push_array(obj_t* self, obj_t* other);
obj_t* obj_array_pop(obj_t* self);
void obj_array_clear(obj_t* self);

size_t obj_array_size(obj_t* self);
obj_t* obj_array_read(obj_t* self, size_t index);
obj_t* obj_array_write(obj_t* self, size_t index, obj_t* obj);

#endif // OBJ_ARRAY_H
