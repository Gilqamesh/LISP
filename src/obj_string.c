#include "universe.h"

static void obj_string_grow(obj_string_t* self);
static void obj_string_shrink(obj_string_t* self);
static void obj_string_push_char(obj_string_t* self, char c);

static void obj_string_grow(obj_string_t* self) {
    if (self->size <= self->top + 1) {
        self->size *= 2;
        self->data = (char*)realloc(self->data, self->size);
        assert(self->data);
    }
}

static void obj_string_shrink(obj_string_t* self) {
    if (0 < self->size && self->top < self->size / 4) {
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

obj_t* obj_string_new() {
    obj_string_t* self = (obj_string_t*) malloc(sizeof(obj_string_t));
    obj_init((obj_t*) self, OBJ_TYPE_STRING);
    self->size = 32;
    self->data = (char*)malloc(self->size);
    assert(self->data);
    self->top = 0;
    self->data[0] = '\0';
    return (obj_t*) self;
}

obj_t* obj_string_new_cstr(const char* format, ...) {
    va_list args;
    va_start(args, format);
    obj_t* result = obj_string_vnew_cstr(format, args);
    va_end(args);
    return result;
}

obj_t* obj_string_vnew_cstr(const char* format, va_list args) {
    obj_t* self = obj_string_new();
    obj_string_vpush_cstr(self, format, args);
    return self;
}

void obj_string_delete(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    free(obj_string->data);
    free(self);
}

bool is_string(obj_t* self) {
    return self->type == OBJ_TYPE_STRING;
}

obj_string_t* obj_as_string(obj_t* self) {
    if (!is_string(self)) {
        throw(obj_string_new_cstr("expected obj_string_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_string_t*) self;
}

ffi_type* obj_string_to_ffi(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    assert(0 && "todo: implement");
}

void obj_string_to_string(obj_t* self, obj_t* string) {
    obj_string_t* obj_string = obj_as_string(self);
    obj_string_push_cstr(string, "<%s \"", obj_type_to_string(obj_get_type(self)));
    obj_string_push_string(string, self);
    obj_string_push_cstr(string, "\">");
}

obj_t* obj_string_copy(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    obj_t* copy = obj_string_new();
    obj_string_push_string(copy, self);
    return copy;
}

bool obj_string_is_equal(obj_t* self, obj_t* other) {
    obj_string_t* obj_string_self = obj_as_string(self);
    obj_string_t* obj_string_other = obj_as_string(other);
    if (obj_string_hash(self) != obj_string_hash(other) || obj_string_size(self) != obj_string_size(other)) {
        return false;
    }
    return obj_string_is_equal_cstr(self, obj_string_cstr(other));
}

bool obj_string_is_truthy(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    assert(0 && "todo: implement");
}

size_t obj_string_hash(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    // DJB2 hash function
    size_t hash = 5381;
    for (size_t i = 0; i < obj_string->top; ++i) {
        hash = ((hash << 5) + hash) + obj_string->data[i];
    }
    return hash;
}

obj_t* obj_string_eval(obj_t* self, obj_t* env) {
    obj_string_t* obj_string = obj_as_string(self);
    return self;
}

obj_t* obj_string_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_string_t* obj_string = obj_as_string(self);
    throw(obj_string_new_cstr("string is not callable"), self);
}

void obj_string_push_cstr(obj_t* self, const char* format, ...) {
    obj_string_t* obj_string = obj_as_string(self);
    va_list args;
    va_start(args, format);
    obj_string_vpush_cstr(self, format, args);
    va_end(args);
}

void obj_string_vpush_cstr(obj_t* self, const char* format, va_list args) {
    obj_string_t* obj_string = obj_as_string(self);
    obj_string_grow(obj_string);
    char buffer[1024];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    assert(0 <= len);
    for (int i = 0; i < len; i++) {
        obj_string_push_char(obj_string, buffer[i]);
    }
}

void obj_string_push_string(obj_t* self, obj_t* string) {
    obj_string_t* obj_string = obj_as_string(self);
    const size_t size_str = obj_string_size(string);
    for (size_t i = 0; i < size_str; ++i) {
        obj_string_push_char(obj_string, obj_string_at(string, i));
    }
}

char obj_string_pop(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    if (obj_string_size(self) == 0) {
        throw(obj_string_new_cstr("empty string"), self);
    }
    char result = obj_string->data[--obj_string->top];
    obj_string->data[obj_string->top] = '\0';
    obj_string_shrink(obj_string);
    return result;
}

void obj_string_clear(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    obj_string->top = 0;
    obj_string->data[0] = '\0';
}

const char* obj_string_cstr(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    return obj_string->data;
}

char obj_string_at(obj_t* self, size_t index) {
    obj_string_t* obj_string = obj_as_string(self);
    if (obj_string->top <= index) {
        throw(obj_string_new_cstr("index out of bounds"), self, obj_i32_new(index));
    }
    return obj_string->data[index];
}

size_t obj_string_size(obj_t* self) {
    obj_string_t* obj_string = obj_as_string(self);
    return obj_string->top;
}

bool obj_string_is_equal_cstr(obj_t* self, const char* cstr) {
    obj_string_t* obj_string = obj_as_string(self);
    return strcmp(obj_string_cstr(self), cstr) == 0;
}
