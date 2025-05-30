#include "universe.h"

static void obj_string_rehash(obj_string_t* self);
static void obj_string_grow(obj_string_t* self);
static void obj_string_shrink(obj_string_t* self);
static void obj_string_push_char(obj_string_t* self, char c);
static void obj_string_vpush(obj_string_t* self, const char* format, va_list args);

static void obj_string_rehash(obj_string_t* self) {
    // DJB2 hash function
    self->hash = 5381;
    const size_t s_size = obj_string_size(self);
    for (size_t i = 0; i < s_size; ++i) {
        self->hash = ((self->hash << 5) + self->hash) + self->data[i];
    }
}

static void obj_string_grow(obj_string_t* self) {
    if (self->size <= self->top + 1) {
        self->size *= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void obj_string_shrink(obj_string_t* self) {
    if (0 < obj_string_size(self) && self->top < self->size / 4) {
        self->size /= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void obj_string_push_char(obj_string_t* self, char c) {
    obj_string_grow(self);
    self->data[self->top++] = c;
    assert(self->top < self->size);
    self->data[self->top] = '\0';
}

static void obj_string_vpush(obj_string_t* self, const char* format, va_list args) {
    obj_string_grow(self);
    char buffer[1024];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    assert(0 <= len);
    for (int i = 0; i < len; i++) {
        obj_string_push_char(self, buffer[i]);
    }
    obj_string_rehash(self);
}

obj_string_t* obj_string_new() {
    obj_string_t* self = (obj_string_t*) malloc(sizeof(obj_string_t));
    obj_init((obj_t*) self, OBJ_TYPE_STRING);
    self->size = 32;
    self->data = (char*)malloc(self->size);
    assert(self->data);
    self->top = 0;
    self->data[0] = '\0';
    obj_string_hash(self);
    return self;
}

obj_string_t* obj_string_new_cstr(const char* format, ...) {
    va_list args;
    va_start(args, format);
    obj_string_t* result = obj_string_vnew_cstr(format, args);
    va_end(args);
    return result;
}

obj_string_t* obj_string_vnew_cstr(const char* format, va_list args) {
    obj_string_t* self = obj_string_new();
    obj_string_vpush(self, format, args);
    return self;
}

void obj_string_delete(obj_string_t* self) {
    free(self->data);
    free(self);
}

bool is_string(const obj_t* self) {
    return self->type == OBJ_TYPE_STRING;
}

obj_ffi_t* obj_string_to_ffi(const obj_string_t* self) {
    assert(0 && "todo: implement");
}

void obj_string_to_string(const obj_string_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<string ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_string(other, self);
    obj_string_push_cstr(other, ">");
}

obj_string_t* obj_string_copy(const obj_string_t* self) {
    obj_string_t* copy = obj_string_new();
    obj_string_push_string(copy, self);
    return copy;
}

bool obj_string_equal(const obj_string_t* self, const obj_string_t* other) {
    if (obj_string_hash(self) != obj_string_hash(other) || obj_string_size(self) != obj_string_size(other)) {
        return false;
    }
    return obj_string_equal_cstr(self, obj_string_cstr(other));
}

size_t obj_string_hash(const obj_string_t* self) {
    return self->hash;
}

obj_t* obj_string_eval(const obj_string_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_string_apply(const obj_string_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}

void obj_string_push_cstr(obj_string_t* self, const char* format, ...) {
    va_list args;
    va_start(args, format);
    obj_string_vpush(self, format, args);
    va_end(args);
}

void obj_string_push_string(obj_string_t* self, const obj_string_t* other) {
    const size_t size_str = obj_string_size(other);
    for (size_t i = 0; i < size_str; ++i) {
        obj_string_push_char(self, obj_string_at(other, i));
    }
    obj_string_rehash(self);
}

char obj_string_pop(obj_string_t* self) {
    if (obj_string_size(self) == 0) {
        throw(obj_string_new_cstr("empty string"), self);
    }
    char result = self->data[--self->top];
    self->data[self->top] = '\0';
    obj_string_shrink(self);
    obj_string_rehash(self);
    return result;
}

void obj_string_clear(obj_string_t* self) {
    self->top = 0;
    self->data[0] = '\0';
    obj_string_rehash(self);
}

const char* obj_string_cstr(const obj_string_t* self) {
    return self->data;
}

char obj_string_at(const obj_string_t* self, size_t index) {
    if (self->top <= index) {
        throw(obj_string_new_cstr("index out of bounds"), (obj_t*) self, (obj_t*) obj_int_new(index));
    }
    return self->data[index];
}

size_t obj_string_size(const obj_string_t* self) {
    return self->top;
}

bool obj_string_equal_cstr(const obj_string_t* self, const char* cstr) {
    return strcmp(obj_string_cstr(self), cstr) == 0;
}
