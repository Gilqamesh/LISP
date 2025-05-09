#include "str_test.h"
#include "str.h"

void str_test() {
    str_t str = str_create("Hello, %s!", "World");
    assert(!str_is_empty(&str));
    assert(str_size(&str) == 13);

    assert(str_at(&str, 0) == 'H');
    assert(str_at(&str, 1) == 'e');
    assert(str_at(&str, 2) == 'l');
    assert(str_is_equal_cstr(&str, "Hello, World!"));
    str_push(&str, "bc");
    assert(str_size(&str) == 15);
    assert(str_is_equal_cstr(&str, "Hello, World!bc"));

    str_clear(&str);
    assert(str_is_empty(&str));
    assert(str_size(&str) == 0);
    str_push(&str, "Hello, %s!", "World");

    str_t str2 = str_create_str(&str);
    assert(str_size(&str2) == 13);

    str_push_str(&str2, &str);
    assert(str_size(&str2) == 26);

    while (!str_is_empty(&str)) {
        size_t str_prev_size = str_size(&str);
        str_pop(&str);
        assert(str_size(&str) == str_prev_size - 1);
    }

    str_destroy(&str);
    str_destroy(&str2);
}
