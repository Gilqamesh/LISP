#ifndef OBJ_LIST_H
# define OBJ_LIST_H

# include "obj.h"

typedef struct obj_list_t {
    obj_t base;
    darr_t objs;
} obj_list_t;

obj_t* obj_list_new();
void obj_list_delete(obj_list_t* self);

bool is_list(obj_t* self);
ffi_type* obj_list_to_ffi(obj_list_t* self);
void obj_list_to_string(obj_list_t* self, obj_t* string;
obj_list_t* obj_list_copy(obj_list_t* self);
bool obj_list_equal(obj_list_t* self, obj_list_t* other);
bool obj_list_is_truthy(obj_list_t* self);
size_t obj_list_hash(obj_list_t* self);
obj_t* obj_list_eval(obj_list_t* self, obj_t* env);
obj_t* obj_list_apply(obj_list_t* self, obj_t* args, obj_t* env);

obj_t* obj_list_push(obj_list_t* self, obj_t* obj);

size_t obj_list_size(obj_list_t* self);
obj_t* obj_list_at(obj_list_t* self, size_t index);
obj_t* obj_list_assign(obj_list_t* self, size_t index, obj_t* obj);

obj_t* obj_list_first(obj_list_t* self);
obj_t* obj_list_last(obj_list_t* self);
obj_t* obj_list_next(obj_list_t* self, obj_t* entry);
obj_t* obj_list_prev(obj_list_t* self, obj_t* entry);

#endif // OBJ_LIST_H
