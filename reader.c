#include "reader.h"

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
    while (reader_is_at_end(self, file)) {
        char c = reader_get_char(self, file);
        size_t child_index = (unsigned char)c;
        if (sizeof(self->root.children) / sizeof(self->root.children[0]) <= child_index) {
            assert(0);
        }
        if (c == ')' || self->root.children[child_index]) {
            reader_unget_char(self, file, c);
            break;
        }
        str_push_char(&lexeme, c);
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
    str_t lexeme;
    reader_function_t reader_function = 0;
    while (node && reader_is_at_end(self, file)) {
        char c = reader_get_char(self, file);
        str_push_char(&lexeme, c);
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
        result = reader_function(self, file);
    } else {
        result = reader_default_function(self, file, lexeme);
    }

    if (is_void(result)) {
        return reader_read(self, file);
    }

    return result;
}
