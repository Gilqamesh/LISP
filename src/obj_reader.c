#include "universe.h"

static void reader_node_init(reader_node_t* self);

static void reader_node_init(reader_node_t* self) {
    memset(self->children, 0, sizeof(self->children));
}

obj_t* obj_reader_new(obj_t* file, reader_fn_t default_reader_fn) {
    obj_reader_t* self = (obj_reader_t*) malloc(sizeof(obj_reader_t));
    obj_init((obj_t*) self, OBJ_TYPE_READER);
    self->file = file;
    reader_node_init(&self->reader_node);
    self->default_reader_fn = default_reader_fn;
    return (obj_t*) self;
}

void obj_reader_delete(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    obj_file_delete(obj_reader->file);
    free(self);
}

bool is_reader(obj_t* self) {
    return self->type == OBJ_TYPE_READER;
}

obj_reader_t* obj_as_reader(obj_t* self) {
    if (!is_reader(self)) {
        throw(obj_string_new_cstr("expected obj_reader_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_reader_t*) self;
}

ffi_type* obj_reader_to_ffi(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    assert(0 && "todo: implement");
}

void obj_reader_to_string(obj_t* self, obj_t* string) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_string_push_cstr(string, "file: ");
    obj_file_to_string(obj_reader->file, string);
    obj_string_push_cstr(string, ", default_reader_fn: ");
    if (obj_reader->default_reader_fn) {
        char buffer[256];
        addr_to_string((void*) obj_reader->default_reader_fn, buffer, sizeof(buffer));
        obj_string_push_cstr(string, "%s", buffer);
    } else {
        obj_string_push_cstr(string, "none");
    }
    obj_string_push_cstr(string, ">");
}

obj_t* obj_reader_copy(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    obj_t* copy = obj_reader_new(obj_file_copy(obj_reader->file), obj_reader->default_reader_fn);
    return copy;
}

bool obj_reader_is_equal(obj_t* self, obj_t* other) {
    obj_reader_t* obj_reader_self = obj_as_reader(self);
    obj_reader_t* obj_reader_other = obj_as_reader(other);
    assert(0 && "todo: implement");
}

bool obj_reader_is_truthy(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    assert(0 && "todo: implement");
}

size_t obj_reader_hash(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    assert(0 && "todo: implement");
}

obj_t* obj_reader_eval(obj_t* self, obj_t* env) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    return self;
}

obj_t* obj_reader_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

obj_t* obj_reader_add_reader_function(obj_t* self, const char* prefix, reader_fn_t reader_fn) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    reader_node_t* node = &obj_reader->reader_node;
    while (*prefix) {
        const size_t child_index = (size_t) *prefix;
        assert(child_index < sizeof(node->children) / sizeof(node->children[0]));
        if (!node->children[child_index]) {
            node->children[child_index] = (reader_node_t*) malloc(sizeof(reader_node_t));
            reader_node_init(node->children[child_index]);
        }
        node = node->children[child_index];
        ++prefix;
    }
    node->reader_fn = reader_fn;
}

obj_t* obj_reader_add_reader_function_char(obj_t* self, char c, reader_fn_t reader_fn) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    const size_t child_index = c;
    assert(child_index < sizeof(obj_reader->reader_node.children) / sizeof(obj_reader->reader_node.children[0]));
    if (!obj_reader->reader_node.children[child_index]) {
        obj_reader->reader_node.children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
        reader_node_init(obj_reader->reader_node.children[child_index]);
    }
    obj_reader->reader_node.children[child_index]->reader_fn = reader_fn;
}

obj_t* obj_reader_read(obj_t* self) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    if (obj_file_is_at_end(obj_reader->file)) {
        return (obj_t*) obj_eof_new();
    }

    reader_node_t* node = &obj_reader->reader_node;
    reader_fn_t reader_fn = 0;
    obj_t* lexeme = obj_string_new();
    while (node && !obj_file_is_at_end(obj_reader->file)) {
        char c = obj_file_read_char(obj_reader->file);
        obj_string_push_cstr(lexeme, "%c", c);
        const size_t child_index = (size_t) c;
        assert(child_index <= sizeof(node->children) / sizeof(node->children[0]));
        node = node->children[child_index];
        if (node && node->reader_fn) {
            reader_fn = node->reader_fn;
            obj_string_clear(lexeme);
        }
    }

    obj_t* result = 0;
    if (reader_fn) {
        while (obj_string_size(lexeme)) {
            char c = obj_string_pop(lexeme);
            obj_file_unread_char(obj_reader->file, c);
        }
        result = reader_fn(obj_reader->file, lexeme);
    } else {
        while (!obj_file_is_at_end(obj_reader->file)) {
            char c = obj_file_read_char(obj_reader->file);
            size_t child_index = (unsigned char)c;
            if (sizeof(obj_reader->reader_node.children) / sizeof(obj_reader->reader_node.children[0]) <= child_index) {
                assert(0);
            }
            if (obj_reader->reader_node.children[child_index]) {
                // if (obj_reader->is_top_level) {
                    obj_file_unread_char(obj_reader->file, c);
                // }
                break ;
            }
            obj_string_push_cstr(lexeme, "%c", c);
        }
        result = obj_reader->default_reader_fn(obj_reader->file, lexeme);
    }

    if (is_void(result)) {
        result = obj_reader_read(self);
    }

    return result;
}

obj_t* obj_reader_default_reader(obj_t* self, obj_t* lexeme) {
    obj_t* result = NULL;

    const size_t lexeme_size = obj_string_size(lexeme);
    if (obj_string_size(lexeme) == 0) {
        result = obj_void_new();
    } else if ((obj_string_at(lexeme, 0) == '.' && 1 < lexeme_size) || isdigit(obj_string_at(lexeme, 0))) {
        bool had_dot = false;
        for (size_t i = 0; result == NULL && i < lexeme_size; ++i) {
            char c = obj_string_at(lexeme, i);
            if (c == '.') {
                if (!had_dot) {
                    had_dot = true;
                } else {
                    result = obj_symbol_new(lexeme);
                }
            } else if (isdigit(c)) {
            } else {
                result = obj_symbol_new(lexeme);
            }
        }

        if (result == NULL) {
            double r64 = atof(obj_string_cstr(lexeme));
            int32_t i32 = r64;
            if (r64 == (double) i32) {
                result = obj_i32_new(i32);
            } else {
                result = obj_r64_new(r64);
            }
        }
    } else {
        result = obj_symbol_new(lexeme);
    }

    return result;
}

obj_t* obj_reader_skip_whitespaces_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    while (!obj_file_is_at_end(obj_reader->file) && isspace(obj_file_peek_char(obj_reader->file))) {
        obj_file_read_char(obj_reader->file);
    }
    return obj_void_new();
}

obj_t* obj_reader_left_paren_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    obj_t* result = obj_nil_new();
    obj_t** head = &result;
    while (!obj_file_is_at_end(obj_reader->file)) {
        obj_reader_skip_whitespaces_reader(self, lexeme);
        if (obj_file_is_at_end(obj_reader->file)) {
            break ;
        }
        switch (obj_file_peek_char(obj_reader->file)) {
        case ')': {
            obj_file_read_char(obj_reader->file);
            *head = obj_nil_new();
            return result;
        } break ;
        default: {
            *head = obj_cons_new(obj_reader_read(self), obj_nil_new());
            head = &obj_as_cons(*head)->cdr;
        } break ;
        }
    }
    throw(obj_string_new_cstr("unmatched left parenthesis"), self);
}

obj_t* obj_reader_right_paren_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    throw(obj_string_new_cstr("unmatched right parenthesis"), self, lexeme);
}

obj_t* obj_reader_double_quote_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    while (!obj_file_is_at_end(obj_reader->file)) {
        char c = obj_file_read_char(obj_reader->file);
        if (c == '"') {
            return lexeme;
        }
        obj_string_push_cstr(lexeme, "%c", c);
    }
    throw(obj_string_new_cstr("unterminated string literal"), self, lexeme);
}

obj_t* obj_reader_quote_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    return obj_cons_new(obj_symbol_new(obj_string_new_cstr("quote")), obj_reader_read(self));
}

obj_t* obj_reader_backtick_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    return obj_cons_new(obj_symbol_new(obj_string_new_cstr("quasiquote")), obj_reader_read(self));
}

obj_t* obj_reader_comma_reader(obj_t* self, obj_t* lexeme) {
    obj_reader_t* obj_reader = obj_as_reader(self);
    if (obj_file_is_at_end(obj_reader->file)) {
        throw(obj_string_new_cstr("unexpected end of file after ','"), self);
    }
    switch (obj_file_read_char(obj_reader->file)) {
    case '@': {
        return obj_cons_new(obj_symbol_new(obj_string_new_cstr("unquote-splicing")), obj_reader_read(self));
    } break ;
    default: {
        return obj_cons_new(obj_symbol_new(obj_string_new_cstr("unquote")), obj_reader_read(self));
    }
    }
}
