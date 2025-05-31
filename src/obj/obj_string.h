#ifndef OBJ_STRING_H
# define OBJ_STRING_H

# include "obj.h"

typedef struct obj_string_t {
    obj_t base;
    char* data;
    size_t top;
    size_t size;
    size_t hash;
} obj_string_t;

obj_string_t* obj_string_new();
obj_string_t* obj_string_new_cstr(const char* format, ...);
obj_string_t* obj_string_vnew_cstr(const char* format, va_list args);
void obj_string_delete(obj_string_t* self);

bool is_string(const obj_t* self);
obj_ffi_t* obj_string_to_ffi(const obj_string_t* self);
void obj_string_to_string(const obj_string_t* self, obj_string_t* other);
obj_string_t* obj_string_copy(const obj_string_t* self);
bool obj_string_equal(const obj_string_t* self, const obj_string_t* other);
size_t obj_string_hash(const obj_string_t* self);
obj_t* obj_string_eval(const obj_string_t* self, obj_env_t* env);
obj_t* obj_string_apply(const obj_string_t* self, obj_array_t* args, obj_env_t* env);

void obj_string_push_cstr(obj_string_t* self, const char* format, ...);
void obj_string_push_string(obj_string_t* self, const obj_string_t* other);
char obj_string_pop(obj_string_t* self);
void obj_string_clear(obj_string_t* self);

const char* obj_string_cstr(const obj_string_t* self);
char obj_string_at(const obj_string_t* self, size_t index);
size_t obj_string_size(const obj_string_t* self);
bool obj_string_equal_cstr(const obj_string_t* self, const char* cstr);

#endif // OBJ_STRING_H
