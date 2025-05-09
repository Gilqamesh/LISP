#ifndef STR_H
# define STR_H

# include "libc.h"

typedef struct str_t {
    char* data;
    size_t top;
    size_t size;
} str_t;

str_t str();
str_t str_create(const char* format, ...);
str_t str_vcreate(const char* format, va_list args);
str_t str_create_str(const str_t* str);
void str_destroy(str_t* self);

void str_push(str_t* self, const char* format, ...);
void str_push_str(str_t* self, const str_t* s);
char str_pop(str_t* self);
void str_clear(str_t* self);

const char* str_data(const str_t* self);
char str_at(const str_t* self, size_t index);
size_t str_size(const str_t* self);
bool str_is_empty(const str_t* self);
bool str_is_equal_str(const str_t* self, const str_t* other);
bool str_is_equal_cstr(const str_t* self, const char* cstr);

#endif // STR_H
