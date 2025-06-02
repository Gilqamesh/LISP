#ifndef OBJ_ERROR_H
# define OBJ_ERROR_H

# include "obj.h"

typedef struct obj_error_t {
    obj_t base;
    obj_t* message;
    obj_t* backtrace_info;
} obj_error_t;

obj_t* obj_error_new(obj_t* message, const char* stringified_args, ... /* objs, NULL */);
// example usage: err(str_create_cstr("blah"), obj1, obj2)
# define throw(message, ...) obj_error_new(message, #__VA_ARGS__, __VA_ARGS__, 0)
void obj_error_delete(obj_t* self);

bool is_error(obj_t* self);
obj_error_t* obj_as_error(obj_t* self);
ffi_type* obj_error_to_ffi(obj_t* self);
void obj_error_to_string(obj_t* self, obj_t* string);
obj_t* obj_error_copy(obj_t* self);
bool obj_error_is_equal(obj_t* self, obj_t* other);
bool obj_error_is_truthy(obj_t* self);
size_t obj_error_hash(obj_t* self);
obj_t* obj_error_eval(obj_t* self, obj_t* env);
obj_t* obj_error_apply(obj_t* self, obj_t* args, obj_t* env);

#endif // OBJ_ERROR_H
