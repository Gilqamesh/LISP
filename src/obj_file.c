#include "obj_file.h"

#include "obj_error.h"
#include "obj_eof.h"
#include "obj_string.h"

static obj_file_t* obj_file_new_internal();

static obj_file_t* obj_file_new_internal() {
    obj_file_t* self = (obj_file_t*) malloc(sizeof(obj_file_t));
    memset(self, 0, sizeof(obj_file_t));
    obj_init((obj_t*) self, OBJ_TYPE_FILE);
    return self;
}

obj_t* obj_file_new(const char* path, const char* mode) {
    obj_file_t* self = obj_file_new_internal();
    strncpy(self->path, path, sizeof(self->path) - 1);
    self->fp = fopen(path, mode);
    self->owns_fp = true;
    if (!self->fp) {
        throw(obj_string_new_cstr("Failed to open file [path: '%s', mode: '%s']", path, mode), self);
    }
    return (obj_t*) self;
}

obj_t* obj_file_new_from_fp(FILE* borrowed_fp) {
    obj_file_t* self = obj_file_new_internal();
    self->fp = borrowed_fp;
    self->owns_fp = false;
    int fd = fileno(borrowed_fp);
    if (fd == -1) {
        throw(obj_string_new_cstr("fileno failed"), self);
    }
    char buffer[256];
    snprintf(buffer, sizeof(buffer) / sizeof(buffer[0]), "/proc/self/fd/%d", fd);
    readlink(buffer, self->path, sizeof(self->path) - 1);
    return (obj_t*) self;
}

void obj_file_delete(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    if (obj_file->owns_fp && obj_file->fp) {
        fclose(obj_file->fp);
    }
    free(self);
}

bool is_file(obj_t* self) {
    return self->type == OBJ_TYPE_FILE;
}

obj_file_t* obj_as_file(obj_t* self) {
    if (!is_file(self)) {
        throw(obj_string_new_cstr("expected obj_file_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_file_t*) self;
}

ffi_type* obj_file_to_ffi(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    assert(0 && "todo: implement");
}

void obj_file_to_string(obj_t* self, obj_t* string) {
    obj_file_t* obj_file = obj_as_file(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_string_push_cstr(string, "'%s'", obj_file->path);
    obj_string_push_cstr(string, ">");
}

obj_t* obj_file_copy(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    assert(0 && "cannot copy file objects");
}

bool obj_file_is_equal(obj_t* self, obj_t* other) {
    obj_file_t* obj_file_self = obj_as_file(self);
    obj_file_t* obj_file_other = obj_as_file(other);
    assert(0 && "todo: implement");
}

bool obj_file_is_truthy(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    assert(0 && "todo: implement");
}

size_t obj_file_hash(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    assert(0 && "todo: implement");
}

obj_t* obj_file_eval(obj_t* self, obj_t* env) {
    obj_file_t* obj_file = obj_as_file(self);
    return self;
}

obj_t* obj_file_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_file_t* obj_file = obj_as_file(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

char obj_file_peek_char(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    char result = obj_file_read_char(self);
    obj_file_unread_char(self, result);
    return result;
}

char obj_file_read_char(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    return fgetc(obj_file->fp);
}

void obj_file_unread_char(obj_t* self, char c) {
    obj_file_t* obj_file = obj_as_file(self);
    ungetc(c, obj_file->fp);
}

bool obj_file_is_at_end(obj_t* self) {
    obj_file_t* obj_file = obj_as_file(self);
    char c = obj_file_read_char(self);
    if (c == EOF) {
        return true;
    }
    obj_file_unread_char(self, c);
    return false;
}
