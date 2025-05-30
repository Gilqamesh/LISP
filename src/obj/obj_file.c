#include "obj_file.h"

#include "obj_error.h"
#include "obj_eof.h"
#include "obj_string.h"

static char obj_file_peek_char(const obj_file_t* self);
static char obj_file_read_char(const obj_file_t* self);
static void obj_file_unread_char(const obj_file_t* self, char c);
static bool obj_file_is_at_end(const obj_file_t* self);

static char obj_file_peek_char(const obj_file_t* self) {
    char result = obj_file_read_char(self);
    obj_file_unread_char(self, result);
    return result;
}

static char obj_file_read_char(const obj_file_t* self) {
    return fgetc(self->fp);
}

static void obj_file_unread_char(const obj_file_t* self, char c) {
    ungetc(c, self->fp);
}

static bool obj_file_is_at_end(const obj_file_t* self) {
    long current_pos = ftell(self->fp);
    fseek(self->fp, 0, SEEK_END);
    long end_pos = ftell(self->fp);
    fseek(self->fp, current_pos, SEEK_SET);
    return end_pos <= current_pos;
}

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

obj_t* obj_file_copy(const obj_file_t* self) {
    assert(0 && "cannot copy file objects");
}

bool obj_file_equal(const obj_file_t* self, const obj_file_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_file_hash(const obj_file_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_file_eval(const obj_file_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_file_apply(const obj_file_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}

obj_t* obj_file_read(const obj_file_t* self) {
    while (!obj_file_is_at_end(self) && isspace(obj_file_peek_char(self))) {
        obj_file_read_char(self);
    }

    if (obj_file_is_at_end(self)) {
        return (obj_t*) obj_eof_new();
    }

    switch (obj_file_read_char(self)) {
    case '"': {
        obj_string_t* lexeme = obj_string_new();
        while (!obj_file_is_at_end(self)) {
            char c = obj_file_read_char(self);
            if (c == '"') {
                return (obj_t*) lexeme;
            }
            obj_string_push_cstr(lexeme, "%c", c);
        }
        throw(obj_string_new_cstr("Unterminated string literal"), lexeme);
    } break ;
    case '\'': {
    } break ;
    case '`': {
    } break ;
    case ',': {
    } break ;
    case '(': {
    } break ;
    case ')': {
    } break ;
    default: {
    } break ;
    }

    assert(0 && "unreachable");
}

obj_t* obj_file_write(const obj_file_t* self, const obj_t* obj) {
}
