#include "obj_string.h"

int main(int argc, char** argv) {
    universe_init(argc, argv);

    try {
        obj_string_t* str = obj_string_new();
        const char* expected = "Hello, World!";
        obj_string_push_cstr(str, "Hello, %s!", "World");
        assert(obj_string_equal_cstr(str, expected));
        assert(obj_string_size(str) == strlen(expected));

        obj_string_push_cstr(str, " Another string.");
        expected = "Hello, World! Another string.";
        assert(obj_string_equal_cstr(str, expected));
        assert(obj_string_size(str) == strlen(expected));

        char popped_char = obj_string_pop(str);
        expected = "Hello, World! Another string";
        assert(popped_char == '.');
        assert(obj_string_equal_cstr(str, expected));
        assert(obj_string_size(str) == strlen(expected));

        obj_string_clear(str);
        expected = "";
        assert(obj_string_size(str) == strlen(expected));
        assert(obj_string_equal_cstr(str, expected));

        obj_string_push_cstr(str, "Final string.");
        expected = "Final string.";
        assert(obj_string_equal_cstr(str, expected));
        assert(obj_string_size(str) == strlen(expected));

        obj_string_t* copy = obj_string_copy(str);
        assert(obj_string_equal(str, copy));
        assert(obj_string_size(copy) == strlen(expected));
        assert(obj_string_equal_cstr(copy, expected));
        assert(obj_string_hash(copy) == obj_string_hash(str));

        obj_string_delete(copy);
        obj_string_delete(str);
    } catch {
        obj_t* err = (obj_t*) err_catch_context();
        obj_string_t* str = obj_string_new();
        obj_to_string(err, str);
        printf("%s\n", obj_string_cstr(str));
        obj_string_delete(str);
    }

    universe_destroy();

    return 0;
}
