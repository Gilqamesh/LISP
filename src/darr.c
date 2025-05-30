#include "darr.h"

static void* darr_at(const darr_t* self, size_t index);
static double darr_load_factor(const darr_t* self);
static void darr_change_size(darr_t* self, size_t new_size);
static void darr_grow(darr_t* self);
static void darr_shrink(darr_t* self);

static void* darr_at(const darr_t* self, size_t index) {
    assert(index < self->elements_top);
    return (char*)self->elements + index * self->size_each;
}

static double darr_load_factor(const darr_t* self) {
    if (self->elements_size == 0) {
        return 1.0;
    }
    return (double)self->elements_top / (double)self->elements_size;
}

static void darr_change_size(darr_t* self, size_t new_size) {
    assert(new_size && !(new_size & (new_size - 1)) && "must be power of 2");
    if (self->elements_size == new_size) {
        return ;
    }
    if (self->elements) {
        self->elements = realloc(self->elements, new_size * self->size_each);
    } else {
        self->elements = malloc(new_size * self->size_each);
    }
    assert(self->elements != NULL);
    self->elements_size = new_size;
    if (self->elements_size < self->elements_top) {
        self->elements_top = self->elements_size;
    }
}

static void darr_grow(darr_t* self) {
    if (self->elements_top < self->elements_size) {
        return ;
    }
    darr_change_size(self, self->elements_size ? self->elements_size * 2 : 16);
}

static void darr_shrink(darr_t* self) {
    if (16 < self->elements_size && darr_load_factor(self) < 0.5) {
        darr_change_size(self, self->elements_size / 2);
    }
}

darr_t darr_new(size_t size_each) {
    darr_t self;
    memset(&self, 0, sizeof(self));
    self.size_each = size_each;
    return self;
}

void darr_delete(darr_t* self) {
    if (self->elements) {
        free(self->elements);
    }
    memset(self, 0, sizeof(*self));
}

void darr_push(darr_t* self, const void* element) {
    darr_grow(self);
    darr_write(self, self->elements_top, element);
    ++self->elements_top;
}

void darr_push_array(darr_t* self, const void* elements, size_t count) {
    const size_t desired_size = self->elements_top + count;
    if (self->elements_size < desired_size) {
        // grow to the next power of 2
        size_t new_size = self->elements_size ? self->elements_size : 1;
        while (new_size < desired_size) {
            new_size *= 2;
        }
        darr_change_size(self, new_size);
    }
    assert(desired_size <= self->elements_size);
    memcpy(darr_at(self, self->elements_top), elements, count * self->size_each);
    self->elements_top += count;
}

void darr_pop(darr_t* self) {
    assert(self->elements_top);
    --self->elements_top;
    darr_shrink(self);
}

void darr_clear(darr_t* self) {
    if (self->elements) {
        free(self->elements);
        self->elements = NULL;
    }
    self->elements_size = 0;
    self->elements_top = 0;
}

size_t darr_size_each(const darr_t* self) {
    return self->size_each;
}

size_t darr_size(const darr_t* self) {
    return self->elements_top;
}

void darr_read(const darr_t* self, size_t index, void* out_element) {
    assert(index < self->elements_top);
    memcpy(out_element, darr_at(self, index), self->size_each);
}

void darr_write(darr_t* self, size_t index, const void* element) {
    assert(index < self->elements_top);
    memcpy(darr_at(self, index), element, self->size_each);
}
