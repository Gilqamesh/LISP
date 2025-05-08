#include "str.h"

static void str_init(str_t* self, size_t size) {
    assert(size);
    self->data = (char*)malloc(size);
    assert(self->data);
    self->top = 0;
    self->size = size;
    self->data[0] = '\0';
}

static void str_grow(str_t* self) {
    if (self->size <= self->top + 1) {
        self->size *= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void str_shrink(str_t* self) {
    if (!str_is_empty(self) && self->top < self->size / 4) {
        self->size /= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

str_t str_create_char(char c) {
    str_t self;
    str_init(&self, 2);
    str_push_char(&self, c);
    return self;
}

str_t str_create_cstr(const char* cstr) {
    str_t self;
    str_init(&self, strlen(cstr) + 1);
    str_push_cstr(&self, cstr);
    return self;
}

str_t str_create_str(const str_t* str) {
    str_t self;
    str_init(&self, str_size(str) + 1);
    str_push_str(&self, str);
    return self;
}

str_t str_create_real(double real) {
    str_t self;
    str_init(&self, 32);
    str_push_real(&self, real);
    return self;
}

void str_destroy(str_t* self) {
    free(self->data);
    self->data = NULL;
    self->top = 0;
    self->size = 0;
}

void str_push_char(str_t* self, char c) {
    str_grow(self);
    assert(self->top < self->size);
    self->data[self->top++] = c;
    assert(self->top < self->size);
    self->data[self->top] = '\0';
}

void str_push_cstr(str_t* self, const char* str) {
    while (*str) {
        str_push_char(self, *str++);
    }
}

void str_push_str(str_t* self, const str_t* str) {
    const size_t size_str = str_size(str);
    for (size_t i = 0; i < size_str; i++) {
        str_push_char(self, str_at(str, i));
    }
}

char str_pop(str_t* self) {
    assert(!str_is_empty(self));
    char result = self->data[--self->top];
    self->data[self->top] = '\0';
    str_shrink(self);
    return result;
}

void str_push_real(str_t* self, double real) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%f", real);
    str_push_cstr(self, buffer);
}

void str_clear(str_t* self) {
    self->top = 0;
}

const char* str_data(const str_t* self) {
    return self->data;
}

char str_at(const str_t* self, size_t index) {
    assert(index < self->top);
    return self->data[index];
}

size_t str_size(const str_t* self) {
    return self->top;
}

bool str_is_empty(const str_t* self) {
    return self->top == 0;
}

bool str_is_equal_str(const str_t* self, const str_t* other) {
    if (str_size(self) != str_size(other)) {
        return false;
    }
    size_t size_self = str_size(self);
    for (size_t i = 0; i < size_self; i++) {
        if (str_at(self, i) != str_at(other, i)) {
            return false;
        }
    }
    return true;
}

bool str_is_equal_cstr(const str_t* self, const char* cstr) {
    size_t size_self = str_size(self);
    size_t size_cstr = strlen(cstr);
    if (size_self != size_cstr) {
        return false;
    }
    for (size_t i = 0; i < size_self; i++) {
        if (str_at(self, i) != cstr[i]) {
            return false;
        }
    }
    return true;
}
