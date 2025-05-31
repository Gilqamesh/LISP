#include "universe.h"

static void reader_node_init(reader_node_t* self);

static obj_t* obj_reader_read_left_paren(obj_reader_t* self);

static void reader_node_init(reader_node_t* self) {
    memset(self->children, 0, sizeof(self->children));
}

static obj_t* obj_reader_read_left_paren(obj_reader_t* self) {
    obj_array_t* args = obj_array_new();
    while (!obj_file_is_at_end(self->file)) {
        while (!obj_file_is_at_end(self->file) && isspace(obj_file_peek_char(self->file))) {
            obj_file_read_char(self->file);
        }
        switch (obj_file_peek_char(self->file)) {
        case ')': {
            obj_file_read_char(self->file);
            return (obj_t*) args;
        } break ;
        default: {
            obj_t* arg = obj_reader_read(self);
            obj_array_push(args, arg);
            break ;
        } break ;
        }
    }
    throw(obj_string_new_cstr("unmatched left parenthesis"), (obj_t*) self);
}

obj_reader_t* obj_reader_new(obj_file_t* file, reader_fn_t default_reader_fn) {
    obj_reader_t* self = (obj_reader_t*) malloc(sizeof(obj_reader_t));
    obj_init((obj_t*) self, OBJ_TYPE_READER);
    self->file = file;
    reader_node_init(&self->reader_node);
    self->default_reader_fn = default_reader_fn;
    self->lexeme = obj_string_new();
    return self;
}

void obj_reader_delete(obj_reader_t* self) {
    obj_file_delete(self->file);
    obj_string_delete(self->lexeme);
    free(self);
}

bool is_reader(const obj_t* self) {
    return self->type == OBJ_TYPE_READER;
}

obj_ffi_t* obj_reader_to_ffi(const obj_reader_t* self) {
    assert(0 && "todo: implement");
}

void obj_reader_to_string(const obj_reader_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<reader ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(other, ">");
}

obj_reader_t* obj_reader_copy(const obj_reader_t* self) {
    obj_reader_t* copy = obj_reader_new(obj_file_copy(self->file), self->default_reader_fn);
    return copy;
}

bool obj_reader_equal(const obj_reader_t* self, const obj_reader_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_reader_hash(const obj_reader_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_reader_eval(const obj_reader_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_reader_apply(const obj_reader_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}

obj_t* obj_reader_add_reader_function(obj_reader_t* self, const char* prefix, reader_fn_t reader_fn) {
    reader_node_t* node = &self->reader_node;
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

obj_t* obj_reader_read(obj_reader_t* self) {
    if (obj_file_is_at_end(self->file)) {
        return (obj_t*) obj_eof_new();
    }

    reader_node_t* node = &self->reader_node;
    reader_fn_t reader_fn = 0;
    while (node && !obj_file_is_at_end(self->file)) {
        char c = obj_file_read_char(self->file);
        obj_string_push_cstr(self->lexeme, "%c", c);
        const size_t child_index = (size_t) c;
        assert(child_index <= sizeof(node->children) / sizeof(node->children[0]));
        node = node->children[child_index];
        if (node && node->reader_fn) {
            reader_fn = node->reader_fn;
            obj_string_clear(self->lexeme);
        }
    }

    obj_t* result = 0;
    if (reader_fn) {
        while (obj_string_size(self->lexeme)) {
            char c = obj_string_pop(self->lexeme);
            obj_file_unread_char(self->file, c);
        }
        result = reader_fn(self);
    } else {
        result = self->default_reader_fn(self);
    }

    if (is_void(result)) {
        return obj_reader_read(self);
    }

    return result;


    // while (!obj_file_is_at_end(self->file) && isspace(obj_file_peek_char(self->file))) {
    //     obj_file_read_char(self->file);
    // }

    // if (obj_file_is_at_end(self->file)) {
    //     return (obj_t*) obj_eof_new();
    // }

    // switch (obj_file_read_char(self->file)) {
    // case '"': {
    //     obj_string_t* lexeme = obj_string_new();
    //     while (!obj_file_is_at_end(self->file)) {
    //         char c = obj_file_read_char(self->file);
    //         if (c == '"') {
    //             return (obj_t*) lexeme;
    //         }
    //         obj_string_push_cstr(lexeme, "%c", c);
    //     }
    //     throw(obj_string_new_cstr("unterminated string literal"), lexeme);
    // } break ;
    // case '\'': {
    //     obj_t* arg = obj_reader_read(self);
    //     obj_t* op = (obj_t*) obj_symbol_new(obj_string_new_cstr("quote"));
    //     obj_array_t* args = obj_array_new();
    //     obj_array_push(args, arg);
    //     return (obj_t*) obj_combination_new(op, args);
    // } break ;
    // case '`': {
    //     obj_t* arg = obj_reader_read(self);
    //     obj_t* op = (obj_t*) obj_symbol_new(obj_string_new_cstr("quasiquote"));
    //     obj_array_t* args = obj_array_new();
    //     obj_array_push(args, arg);
    //     return (obj_t*) obj_combination_new(op, args);
    // } break ;
    // case ',': {
    //     if (obj_file_is_at_end(self->file)) {
    //         throw(obj_string_new_cstr("unexpected end of file after ','"), (obj_t*) self);
    //     }
    //     switch (obj_file_read_char(self->file)) {
    //     case '@': {
    //         obj_t* arg = obj_reader_read(self);
    //         obj_t* op = (obj_t*) obj_symbol_new(obj_string_new_cstr("unquote-splicing"));
    //         obj_array_t* args = obj_array_new();
    //         obj_array_push(args, arg);
    //         return (obj_t*) obj_combination_new(op, args);
    //     } break ;
    //     default: {
    //         obj_t* arg = obj_reader_read(self);
    //         obj_t* op = (obj_t*) obj_symbol_new(obj_string_new_cstr("unquote"));
    //         obj_array_t* args = obj_array_new();
    //         obj_array_push(args, arg);
    //         return (obj_t*) obj_combination_new(op, args);
    //     }
    //     }
    // } break ;
    // case '(': {
    //     return obj_reader_read_left_paren(self);
    // } break ;
    // case ')': {
    //     throw(obj_string_new_cstr("unmatched right parenthesis"), (obj_t*) self);
    // } break ;
    // default: {
    // } break ;
    // }

    // assert(0 && "unreachable");
}
