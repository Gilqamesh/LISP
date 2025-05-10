#include "reader.h"
#include "lisp.h"

static obj_t* reader_skip_whitespaces(reader_t* self, FILE* file);
static obj_t* reader_double_quote(reader_t* self, FILE* file);
static obj_t* reader_quote(reader_t* self, FILE* file);
static obj_t* reader_qauasiquote(reader_t* self, FILE* file);
static obj_t* reader_comma(reader_t* self, FILE* file);
static obj_t* reader_right_parent(reader_t* self, FILE* file);
static obj_t* reader_left_parent(reader_t* self, FILE* file);
static obj_t* reader_true(reader_t* self, FILE* file);
static obj_t* reader_false(reader_t* self, FILE* file);
static obj_t* reader_multiline_comment(reader_t* self, FILE* file);

static obj_t* reader_skip_whitespaces(reader_t* self, FILE* file) {
    while (!reader_is_at_end(self, file) && reader_is_whitespace(self, reader_peek(self, file))) {
        reader_get_char(self, file);
    }
    return memory_void(self->memory);
}

static obj_t* reader_double_quote(reader_t* self, FILE* file) {
    str_t lexeme = str();
    while (!reader_is_at_end(self, file)) {
        char c = reader_get_char(self, file);
        if (c == '"') {
            return memory_string(self->memory, lexeme);
        }
        str_push(&lexeme, "%c", c);
    }
    str_t error_message = str_create("Unterminated string literal: ");
    str_push_str(&error_message, &lexeme);
    return memory_error(self->memory, error_message);
}

static obj_t* reader_quote(reader_t* self, FILE* file) {
    list(self->memory, memory_symbol(self->memory, str_create("quote")), reader_read(self, file));
}

static obj_t* reader_qauasiquote(reader_t* self, FILE* file) {
    list(self->memory, memory_symbol(self->memory, str_create("quasiquote")), reader_read(self, file));
}

static obj_t* reader_comma(reader_t* self, FILE* file) {
    if (reader_is_at_end(self, file)) {
        return memory_error(self->memory, str_create("Unexpected end of file after comma"));
    }
    char c = reader_get_char(self, file);
    switch (c) {
        case '@': {
            return list(self->memory, memory_symbol(self->memory, str_create("unquote-splicing")), reader_read(self, file));
        } break ;
        default: {
            reader_unget_char(self, file, c);
            return list(self->memory, memory_symbol(self->memory, str_create("unquote")), reader_read(self, file));
        }
    }
}

static obj_t* reader_right_parent(reader_t* self, FILE* file) {
    return memory_symbol(self->memory, str_create(")"));
}

static obj_t* reader_left_parent(reader_t* self, FILE* file) {
    if (reader_is_at_end(self, file)) {
        return memory_error(self->memory, str_create("Unexpected end of file after left parenthesis"));
    }

    obj_t* obj = reader_read(self, file);
    if (is_eq(obj, memory_symbol(self->memory, str_create(")")))) {
        return memory_nil(self->memory);
    }

    return memory_cons(self->memory, obj, reader_left_parent(self, file));
}

static obj_t* reader_true(reader_t* self, FILE* file) {
    return memory_bool(self->memory, true);
}

static obj_t* reader_false(reader_t* self, FILE* file) {
    return memory_bool(self->memory, false);
}

static obj_t* reader_multiline_comment(reader_t* self, FILE* file) {
    size_t depth = 1;
    return 0;
}

void reader_node_init(reader_node_t* self) {
    memset(self, 0, sizeof(reader_node_t));
}

void reader_node_destroy(reader_node_t* self) {
    for (int i = 0; i < sizeof(self->children) / sizeof(self->children[0]); i++) {
        if (self->children[i]) {
            reader_node_destroy(self->children[i]);
        }
    }
}

void reader_init(reader_t* self, memory_t* memory) {
    memset(self, 0, sizeof(reader_t));

    reader_node_init(&self->root);
    self->memory = memory;
}

void reader_destroy(reader_t* self) {
    reader_node_destroy(&self->root);
}

void reader_register_reader_macro_str(reader_t* self, const char* name, reader_function_t reader_function) {
    reader_node_t* node = &self->root;
    while (*name) {
        const size_t child_index = (unsigned char)*name;
        assert(child_index < sizeof(node->children) / sizeof(node->children[0]));
        if (!node->children[child_index]) {
            node->children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
            reader_node_init(node->children[child_index]);
        }
        node = node->children[child_index];
        ++name;
    }
    node->reader_function = reader_function;
}

void reader_register_reader_macro_char(reader_t* self, char c, reader_function_t reader_function) {
    const size_t child_index = (unsigned char)c;
    assert(child_index < sizeof(self->root.children) / sizeof(self->root.children[0]));
    if (!self->root.children[child_index]) {
        self->root.children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
        reader_node_init(self->root.children[child_index]);
    }
    self->root.children[child_index]->reader_function = reader_function;
}

char reader_peek(reader_t* self, FILE* file) {
    char c = getc(file);
    ungetc(c, file);
    return c;
}

char reader_get_char(reader_t* self, FILE* file) {
    char c = getc(file);
    if (c == EOF) {
        return '\0';
    }
    return c;
}

void reader_unget_char(reader_t* self, FILE* file, char c) {
    ungetc(c, file);
}

bool reader_is_at_end(reader_t* self, FILE* file) {
    char c = reader_get_char(self, file);
    if (c == '\0') {
        return true;
    }
    reader_unget_char(self, file, c);
    return false;
}

bool reader_is_whitespace(reader_t* self, char c) {
    return isspace(c);
}

obj_t* reader_default_function(reader_t* self, FILE* file, str_t lexeme) {
    while (!reader_is_at_end(self, file)) {
        char c = reader_get_char(self, file);
        size_t child_index = (unsigned char)c;
        if (sizeof(self->root.children) / sizeof(self->root.children[0]) <= child_index) {
            assert(0);
        }
        if (c == ')' || self->root.children[child_index]) {
            reader_unget_char(self, file, c);
            break ;
        }
        str_push(&lexeme, "%c", c);
    }

    const size_t lexeme_size = str_size(&lexeme); 
    if (str_is_empty(&lexeme)) {
        return memory_void(self->memory);
    } else if ((str_at(&lexeme, 0) == '.' && 1 < lexeme_size) || isdigit(str_at(&lexeme, 0))) {
        bool had_dot = false;
        for (size_t i = 0; i < lexeme_size; ++i) {
            char c = str_at(&lexeme, i);
            if (c == '.') {
                if (!had_dot) {
                    had_dot = true;
                } else {
                    return memory_symbol(self->memory, lexeme);
                }
            } else if (isdigit(c)) {
            } else {
                return memory_symbol(self->memory, lexeme);
            }
        }
        obj_t* result = memory_real(self->memory, atof(str_data(&lexeme)));
        str_destroy(&lexeme);
        return result;
    } else {
        return memory_symbol(self->memory, lexeme);
    }
}

obj_t* reader_read(reader_t* self, FILE* file) {
    if (reader_is_at_end(self, file)) {
        return memory_eof(self->memory);
    }

    reader_node_t *node = &self->root;
    str_t lexeme = str();
    reader_function_t reader_function = 0;
    while (node && !reader_is_at_end(self, file)) {
        char c = reader_get_char(self, file);
        str_push(&lexeme, "%c", c);
        size_t child_index = (unsigned char)c;
        if (sizeof(node->children) / sizeof(node->children[0]) <= child_index) {
            assert(0);
        }
        node = node->children[child_index];
        if (node && node->reader_function) {
            reader_function = node->reader_function;
            str_clear(&lexeme);
        }
    }

    obj_t* result = 0;
    if (reader_function) {
        while (str_size(&lexeme)) {
            char c = str_pop(&lexeme);
            reader_unget_char(self, file, c);
        }
        result = reader_function(self, file);
    } else {
        result = reader_default_function(self, file, lexeme);
    }

    if (is_void(result)) {
        return reader_read(self, file);
    }

    return result;
}

void reader_register_reader_macros(reader_t* self) {
    for (size_t i = 0; i < sizeof(self->root.children) / sizeof(self->root.children[0]); i++) {
        if (reader_is_whitespace(self, (char)i)) {
            reader_register_reader_macro_char(self, (char)i, &reader_skip_whitespaces);
        }
    }
    reader_register_reader_macro_str(self, "\"", &reader_double_quote);
    reader_register_reader_macro_str(self, "'", &reader_quote);
    reader_register_reader_macro_str(self, "`", &reader_qauasiquote);
    reader_register_reader_macro_str(self, ",", &reader_comma);
    reader_register_reader_macro_str(self, ")", &reader_right_parent);
    reader_register_reader_macro_str(self, "(", &reader_left_parent);
    reader_register_reader_macro_str(self, "#t", &reader_true);
    reader_register_reader_macro_str(self, "#f", &reader_false);
}
