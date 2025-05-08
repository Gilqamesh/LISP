#include "str_test.h"
#include "str.h"

void str_test() {
    str_t str = str_create_char('a');
    assert(!str_is_empty(&str));
    assert(str_size(&str) == 1);
    assert(str_at(&str, 0) == 'a');
    str_push_cstr(&str, "bc");
    assert(str_size(&str) == 3);
    assert(str_at(&str, 1) == 'b');
    assert(str_at(&str, 2) == 'c');

    str_clear(&str);
    assert(str_is_empty(&str));
    assert(str_size(&str) == 0);
    str_push_real(&str, 3.14);
    assert(str_at(&str, 0) == '3');
    assert(str_at(&str, 1) == '.');
    assert(str_at(&str, 2) == '1');
    assert(str_at(&str, 3) == '4');
    
    str_t str2 = str_create_cstr("Hello, World!");
    assert(str_size(&str2) == 13);
    assert(strcmp(str_data(&str2), "Hello, World!") == 0);

    str_push_str(&str2, &str);
    assert(str_size(&str2) == 13 + str_size(&str));

    while (!str_is_empty(&str)) {
        size_t str_prev_size = str_size(&str);
        str_pop(&str);
        assert(str_size(&str) == str_prev_size - 1);
    }

    str_destroy(&str);
    str_destroy(&str2);
}
