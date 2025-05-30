#ifndef OBJ_ERROR_H
# define OBJ_ERROR_H

# include "obj.h"

typedef struct obj_error_t {
    obj_t base;
    obj_string_t* message;
} obj_error_t;

obj_error_t* obj_error_new(obj_string_t* message, const char* file, const char* caller, int line, const char* stringified_args, ... /* objs, NULL */);
// example usage: err(str_create_cstr("blah"), obj1, obj2)
# define throw(message, ...) obj_error_new(message, __FILE__, __FUNCTION__, __LINE__, #__VA_ARGS__, __VA_ARGS__, 0)
void obj_error_delete(obj_error_t* self);

bool is_error(const obj_t* self);
obj_ffi_t* obj_error_to_ffi(const obj_error_t* self);
void obj_error_to_string(const obj_error_t* self, obj_string_t* str);
obj_t* obj_error_copy(const obj_error_t* self);
bool obj_error_equal(const obj_error_t* self, const obj_error_t* other);
size_t obj_error_hash(const obj_error_t* self);
obj_t* obj_error_eval(const obj_error_t* self, obj_hash_table_t* env);
obj_t* obj_error_apply(const obj_error_t* self, obj_array_t* args, obj_hash_table_t* env);

#endif // OBJ_ERROR_H
