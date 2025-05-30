#ifndef STR_H
# define STR_H

# include "libc.h"

typedef struct str_t {
    char* data;
    size_t top;
    size_t size;
    size_t hash;
} str_t;

str_t str_new();
str_t str_copy(const str_t* self);
str_t str_new_cstr(const char* format, ...);
str_t str_vnew_cstr(const char* format, va_list args);
str_t str_new_str(const str_t* str);
void str_delete(str_t* self);

void str_push_cstr(str_t* self, const char* format, ...);
void str_push_str(str_t* self, const str_t* s);
char str_pop(str_t* self);
void str_clear(str_t* self);

const char* str_cstr(const str_t* self);
char str_at(const str_t* self, size_t index);
size_t str_size(const str_t* self);
bool str_cmp_str(const str_t* self, const str_t* other);
bool str_cmp_cstr(const str_t* self, const char* cstr);
size_t str_hash(const str_t* self);

#endif // STR_H
