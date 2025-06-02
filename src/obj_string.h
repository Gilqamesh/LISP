#ifndef OBJ_STRING_H
# define OBJ_STRING_H

# include "obj.h"

typedef struct obj_string_t {
    obj_t base;
    char* data;
    size_t top;
    size_t size;
} obj_string_t;

obj_t* obj_string_new();
obj_t* obj_string_new_cstr(const char* format, ...);
obj_t* obj_string_vnew_cstr(const char* format, va_list args);
void obj_string_delete(obj_t* self);

bool is_string(obj_t* self);
obj_string_t* obj_as_string(obj_t* self);
ffi_type* obj_string_to_ffi(obj_t* self);
void obj_string_to_string(obj_t* self, obj_t* string);
obj_t* obj_string_copy(obj_t* self);
bool obj_string_is_equal(obj_t* self, obj_t* other);
bool obj_string_is_truthy(obj_t* self);
size_t obj_string_hash(obj_t* self);
obj_t* obj_string_eval(obj_t* self, obj_t* env);
obj_t* obj_string_apply(obj_t* self, obj_t* args, obj_t* env);

void obj_string_push_cstr(obj_t* self, const char* format, ...);
void obj_string_vpush_cstr(obj_t* self, const char* format, va_list args);
void obj_string_push_string(obj_t* self, obj_t* string);
char obj_string_pop(obj_t* self);
void obj_string_clear(obj_t* self);

const char* obj_string_cstr(obj_t* self);
char obj_string_at(obj_t* self, size_t index);
size_t obj_string_size(obj_t* self);
bool obj_string_is_equal_cstr(obj_t* self, const char* cstr);

#endif // OBJ_STRING_H
