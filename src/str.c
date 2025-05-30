#include "str.h"

static void str_rehash(str_t* self);
static void str_grow(str_t* self);
static void str_shrink(str_t* self);
static void str_push_char(str_t* self, char c);
static void str_vpush(str_t* self, const char* format, va_list args);

static void str_rehash(str_t* self) {
    // DJB2 hash function
    self->hash = 5381;
    const size_t s_size = str_size(self);
    for (size_t i = 0; i < s_size; ++i) {
        self->hash = ((self->hash << 5) + self->hash) + self->data[i];
    }
}

static void str_grow(str_t* self) {
    if (self->size <= self->top + 1) {
        self->size *= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void str_shrink(str_t* self) {
    if (0 < str_size(self) && self->top < self->size / 4) {
        self->size /= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void str_push_char(str_t* self, char c) {
    str_grow(self);
    self->data[self->top++] = c;
    assert(self->top < self->size);
    self->data[self->top] = '\0';
}

static void str_vpush(str_t* self, const char* format, va_list args) {
    str_grow(self);
    char buffer[1024];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    assert(0 <= len);
    for (int i = 0; i < len; i++) {
        str_push_char(self, buffer[i]);
    }
    str_rehash(self);
}

str_t str_new() {
    str_t self;
    self.size = 32;
    self.data = (char*)malloc(self.size);
    assert(self.data);
    self.top = 0;
    self.data[0] = '\0';
    str_hash(&self);
    return self;
}

str_t str_copy(const str_t* self) {
    str_t str = str_new();
    str_push_str(&str, self);
    return str;
}

str_t str_new_cstr(const char* format, ...) {
    va_list args;
    va_start(args, format);
    str_t result = str_vnew_cstr(format, args);
    va_end(args);
    return result;
}

str_t str_vnew_cstr(const char* format, va_list args) {
    str_t self = str_new();
    str_vpush(&self, format, args);
    return self;
}

str_t str_new_str(const str_t* s) {
    str_t self = str_new();
    str_push_str(&self, s);
    return self;
}

void str_delete(str_t* self) {
    free(self->data);
    self->data = NULL;
    self->top = 0;
    self->size = 0;
}

void str_push_cstr(str_t* self, const char* format, ...) {
    va_list args;
    va_start(args, format);
    str_vpush(self, format, args);
    va_end(args);
}

void str_push_str(str_t* self, const str_t* str) {
    const size_t size_str = str_size(str);
    for (size_t i = 0; i < size_str; ++i) {
        str_push_char(self, str_at(str, i));
    }
    str_rehash(self);
}

char str_pop(str_t* self) {
    assert(0 < str_size(self));
    char result = self->data[--self->top];
    self->data[self->top] = '\0';
    str_shrink(self);
    str_rehash(self);
    return result;
}

void str_clear(str_t* self) {
    self->top = 0;
    str_rehash(self);
}

const char* str_cstr(const str_t* self) {
    return self->data;
}

char str_at(const str_t* self, size_t index) {
    assert(index < self->top);
    return self->data[index];
}

size_t str_size(const str_t* self) {
    return self->top;
}

bool str_cmp_str(const str_t* self, const str_t* other) {
    if (str_hash(self) != str_hash(other) || str_size(self) != str_size(other)) {
        return false;
    }
    return str_cmp_cstr(self, str_cstr(other));
}

bool str_cmp_cstr(const str_t* self, const char* cstr) {
    return strcmp(str_cstr(self), cstr) == 0;
}

size_t str_hash(const str_t* self) {
    return self->hash;
}
