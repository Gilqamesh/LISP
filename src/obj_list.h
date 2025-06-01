#ifndef OBJ_LIST_H
# define OBJ_LIST_H

# include "obj.h"

typedef struct obj_list_t {
    obj_t base;
    darr_t objs;
} obj_list_t;

obj_list_t* obj_list_new();
void obj_list_delete(obj_list_t* self);

bool is_list(const obj_t* self);
obj_ffi_t* obj_list_to_ffi(const obj_list_t* self);
void obj_list_to_string(const obj_list_t* self, obj_string_t* str);
obj_list_t* obj_list_copy(const obj_list_t* self);
bool obj_list_equal(const obj_list_t* self, const obj_list_t* other);
bool obj_list_is_truthy(const obj_list_t* self);
size_t obj_list_hash(const obj_list_t* self);
obj_t* obj_list_eval(const obj_list_t* self, obj_env_t* env);
obj_t* obj_list_apply(const obj_list_t* self, obj_t* args, obj_env_t* env);

obj_t* obj_list_push(obj_list_t* self, obj_t* obj);

size_t obj_list_size(const obj_list_t* self);
obj_t* obj_list_at(const obj_list_t* self, size_t index);
obj_t* obj_list_assign(obj_list_t* self, size_t index, obj_t* obj);

obj_t* obj_list_first(const obj_list_t* self);
obj_t* obj_list_last(const obj_list_t* self);
obj_t* obj_list_next(const obj_list_t* self, obj_t* entry);
obj_t* obj_list_prev(const obj_list_t* self, obj_t* entry);

#endif // OBJ_LIST_H
