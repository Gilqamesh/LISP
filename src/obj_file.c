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

obj_file_t* obj_file_new(const char* path, const char* mode) {
    obj_file_t* self = obj_file_new_internal();
    strncpy(self->path, path, sizeof(self->path) - 1);
    self->fp = fopen(path, mode);
    self->owns_fp = true;
    if (!self->fp) {
        throw(obj_string_new_cstr("Failed to open file [path: '%s', mode: '%s']", path, mode), self);
    }
    return self;
}

obj_file_t* obj_file_new_from_fp(FILE* borrowed_fp) {
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
    return self;
}

void obj_file_delete(obj_file_t* self) {
    if (self->owns_fp && self->fp) {
        fclose(self->fp);
    }
    free(self);
}

bool is_file(const obj_t* self) {
    return self->type == OBJ_TYPE_FILE;
}

obj_ffi_t* obj_file_to_ffi(const obj_file_t* self) {
    assert(0 && "todo: implement");
}

void obj_file_to_string(const obj_file_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(str, "'%s'", self->path);
    obj_string_push_cstr(str, ">");
}

obj_file_t* obj_file_copy(const obj_file_t* self) {
    assert(0 && "cannot copy file objects");
}

bool obj_file_equal(const obj_file_t* self, const obj_file_t* other) {
    assert(0 && "todo: implement");
}

bool obj_file_is_truthy(const obj_file_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_file_hash(const obj_file_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_file_eval(const obj_file_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_file_apply(const obj_file_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}

char obj_file_peek_char(const obj_file_t* self) {
    char result = obj_file_read_char(self);
    obj_file_unread_char(self, result);
    return result;
}

char obj_file_read_char(const obj_file_t* self) {
    return fgetc(self->fp);
}

void obj_file_unread_char(const obj_file_t* self, char c) {
    ungetc(c, self->fp);
}

bool obj_file_is_at_end(const obj_file_t* self) {
    char c = obj_file_read_char(self);
    if (c == EOF) {
        return true;
    }
    obj_file_unread_char(self, c);
    return false;
}
