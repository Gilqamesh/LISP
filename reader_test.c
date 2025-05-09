#include "reader_test.h"
#include "reader.h"
#include "lisp.h"

obj_t* reader_skip_whitespaces(reader_t* self, FILE* file) {
    while (!reader_is_at_end(self, file) && reader_is_whitespace(self, reader_peek(self, file))) {
        reader_get_char(self, file);
    }
    return memory_void(self->memory);
}

obj_t* reader_double_quote(reader_t* self, FILE* file) {
    str_t lexeme;
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

obj_t* reader_quote(reader_t* self, FILE* file) {
    list(self->memory, memory_symbol(self->memory, str_create("quote")), reader_read(self, file));
}

obj_t* reader_qauasiquote(reader_t* self, FILE* file) {
    list(self->memory, memory_symbol(self->memory, str_create("quasiquote")), reader_read(self, file));
}

obj_t* reader_comma(reader_t* self, FILE* file) {
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

obj_t* reader_right_parent(reader_t* self, FILE* file) {
    return memory_symbol(self->memory, str_create(")"));
}

obj_t* reader_left_parent(reader_t* self, FILE* file) {
    if (reader_is_at_end(self, file)) {
        return memory_error(self->memory, str_create("Unexpected end of file after left parenthesis"));
    }

    obj_t* obj = reader_read(self, file);
    if (is_eq(obj, memory_symbol(self->memory, str_create(")")))) {
        return memory_nil(self->memory);
    }

    return memory_cons(self->memory, obj, reader_left_parent(self, file));
}

obj_t* reader_true(reader_t* self, FILE* file) {
    return memory_bool(self->memory, true);
}

obj_t* reader_false(reader_t* self, FILE* file) {
    return memory_bool(self->memory, false);
}

obj_t* reader_multiline_comment(reader_t* self, FILE* file) {
    size_t depth = 1;
}

void test_reader(reader_t* reader) {
    for (size_t i = 0; i < sizeof(reader->root.children) / sizeof(reader->root.children[0]); i++) {
        if (reader_is_whitespace(reader, (char)i)) {
            reader_register_reader_macro_char(reader, (char)i, &reader_skip_whitespaces);
        }
    }
    reader_register_reader_macro_str(reader, "\"", &reader_double_quote);
    reader_register_reader_macro_str(reader, "'", &reader_quote);
    reader_register_reader_macro_str(reader, "`", &reader_qauasiquote);
    reader_register_reader_macro_str(reader, ",", &reader_comma);
    reader_register_reader_macro_str(reader, ")", &reader_right_parent);
    reader_register_reader_macro_str(reader, "(", &reader_left_parent);
    reader_register_reader_macro_str(reader, "#t", &reader_true);
    reader_register_reader_macro_str(reader, "#f", &reader_false);

    FILE* file = fopen("test.txt", "w");
    assert(file != NULL);
    fprintf(file, "(1 2 3 4 5)\n");
    fclose(file);

    file = fopen("test.txt", "r");
    assert(file != NULL);
    obj_t* obj = reader_read(reader, file);
    assert(is_list(obj));
    assert(list_length(obj) == 5);
    assert(is_real(list_ref(obj, 0)));
    assert(get_real(list_ref(obj, 0)) == 1.0);
    assert(is_real(list_ref(obj, 1)));
    assert(get_real(list_ref(obj, 1)) == 2.0);
    assert(is_real(list_ref(obj, 2)));
    assert(get_real(list_ref(obj, 2)) == 3.0);
    assert(is_real(list_ref(obj, 3)));
    assert(get_real(list_ref(obj, 3)) == 4.0);
    assert(is_real(list_ref(obj, 4)));
    assert(get_real(list_ref(obj, 4)) == 5.0);
    fclose(file);
}

void reader_test() {
    memory_t memory;
    reader_t reader;

    memory_init(&memory);
    reader_init(&reader, &memory);

    test_reader(&reader);

    reader_destroy(&reader);
    memory_destroy(&memory);
}
