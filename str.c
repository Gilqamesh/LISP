#include "str.h"

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

static void str_push_char(str_t* self, char c) {
    str_grow(self);
    self->data[self->top++] = c;
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
}

str_t str() {
    str_t self;
    self.size = 32;
    self.data = (char*)malloc(self.size);
    assert(self.data);
    self.top = 0;
    self.data[0] = '\0';
    return self;
}

str_t str_create(const char* format, ...) {
    va_list args;
    va_start(args, format);
    str_t result = str_vcreate(format, args);
    va_end(args);
    return result;
}

str_t str_vcreate(const char* format, va_list args) {
    str_t self = str();
    str_vpush(&self, format, args);
    return self;
}

str_t str_create_str(const str_t* s) {
    str_t self = str();
    str_push_str(&self, s);
    return self;
}

void str_destroy(str_t* self) {
    free(self->data);
    self->data = NULL;
    self->top = 0;
    self->size = 0;
}

void str_push(str_t* self, const char* format, ...) {
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
}

char str_pop(str_t* self) {
    assert(!str_is_empty(self));
    char result = self->data[--self->top];
    self->data[self->top] = '\0';
    str_shrink(self);
    return result;
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
