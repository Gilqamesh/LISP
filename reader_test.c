#include "reader_test.h"
#include "reader.h"
#include "memory.h"

obj_t* reader_skip_whitespaces(reader_t* self, FILE* file) {
    while (!reader_is_at_end(self, file) && reader_is_whitespace(self, reader_peek(self, file))) {
        reader_get_char(self, file);
    }
    return memory_void(self->memory);
}

obj_t* reader_double_quote(reader_t* self, FILE* file) {
}

void test_reader(reader_t* reader) {
    for (size_t i = 0; i < sizeof(reader->root.children) / sizeof(reader->root.children[0]); i++) {
        if (reader_is_whitespace(reader, (char)i)) {
            reader_register_reader_macro_char(reader, (char)i, &reader_skip_whitespaces);
        }
    }
    reader_register_reader_macro_str(reader, "\"", &reader_double_quote);
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
