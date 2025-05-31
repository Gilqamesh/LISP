#include "obj_file.h"

#include "obj_error.h"
#include "obj_eof.h"
#include "obj_string.h"

obj_file_t* obj_file_new(const char* path, const char* mode) {
    obj_file_t* self = (obj_file_t*) malloc(sizeof(obj_file_t));
    obj_init((obj_t*) self, OBJ_TYPE_FILE);
    self->path = path;
    self->fp = fopen(path, mode);
    if (!self->fp) {
        throw(obj_string_new_cstr("Failed to open file [path: '%s', mode: '%s']", path, mode), self);
    }
    return self;
}

void obj_file_delete(obj_file_t* self) {
    if (self->fp) {
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
    obj_string_push_cstr(str, "<file ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(str, "'%s'", self->path);
    obj_string_push_cstr(str, ">");
}

obj_file_t* obj_file_copy(const obj_file_t* self) {
    assert(0 && "cannot copy file objects");
}

bool obj_file_equal(const obj_file_t* self, const obj_file_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_file_hash(const obj_file_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_file_eval(const obj_file_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_file_apply(const obj_file_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
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
    long current_pos = ftell(self->fp);
    fseek(self->fp, 0, SEEK_END);
    long end_pos = ftell(self->fp);
    fseek(self->fp, current_pos, SEEK_SET);
    return end_pos <= current_pos;
}
