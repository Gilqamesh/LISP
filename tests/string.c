#include "universe.h"

int main(int argc, char** argv) {
    universe_init(argc, argv);

    try {
        obj_t* string = obj_string_new();
        const char* expected = "Hello, World!";
        obj_string_push_cstr(string, "Hello, %s!", "World");
        assert(obj_string_is_equal_cstr(string, expected));
        assert(obj_string_size(string) == strlen(expected));

        obj_string_push_cstr(string, " Another string.");
        expected = "Hello, World! Another string.";
        assert(obj_string_is_equal_cstr(string, expected));
        assert(obj_string_size(string) == strlen(expected));

        char popped_char = obj_string_pop(string);
        expected = "Hello, World! Another string";
        assert(popped_char == '.');
        assert(obj_string_is_equal_cstr(string, expected));
        assert(obj_string_size(string) == strlen(expected));

        obj_string_clear(string);
        expected = "";
        assert(obj_string_size(string) == strlen(expected));
        assert(obj_string_is_equal_cstr(string, expected));

        obj_string_push_cstr(string, "Final string.");
        expected = "Final string.";
        assert(obj_string_is_equal_cstr(string, expected));
        assert(obj_string_size(string) == strlen(expected));

        obj_t* copy = obj_string_copy(string);
        assert(obj_string_is_equal(string, copy));
        assert(obj_string_size(copy) == strlen(expected));
        assert(obj_string_is_equal_cstr(copy, expected));
        assert(obj_string_hash(copy) == obj_string_hash(string));

        obj_string_delete(copy);
        obj_string_delete(string);
    } catch {
        obj_t* err = err_catch_context();
        obj_t* string = obj_string_new();
        obj_to_string(err, string);
        printf("%s\n", obj_string_cstr(string));
        obj_string_delete(string);
    }

    universe_deinit();

    return 0;
}
