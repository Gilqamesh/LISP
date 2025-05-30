#ifndef DARR_H
# define DARR_H

# include "libc.h"

typedef struct darr_t {
    size_t size_each;
    size_t elements_size;
    size_t elements_top;
    void* elements;
} darr_t;

darr_t darr_new(size_t size_each);
void darr_delete(darr_t* self);

void darr_push(darr_t* self, const void* element);
void darr_push_array(darr_t* self, const void* elements, size_t count);
void darr_pop(darr_t* self);
void darr_clear(darr_t* self);

size_t darr_size_each(const darr_t* self);
size_t darr_size(const darr_t* self);
void darr_read(const darr_t* self, size_t index, void* out_element);
void darr_write(darr_t* self, size_t index, const void* element);

#endif // DARR_H
