#include "memory_test.h"
#include "memory.h"

void memory_test() {
    memory_t memory;
    memory_init(&memory);

    obj_t* obj_eof = memory_eof(&memory);
    assert(is_eof(obj_eof));

    obj_t* obj_nil = memory_nil(&memory);
    assert(is_nil(obj_nil));

    obj_t* obj_void = memory_void(&memory);
    assert(is_void(obj_void));

    obj_t* obj_real = memory_real(&memory, 3.14);
    assert(is_real(obj_real));

    const char* test_symbol_str = "test_string";
    str_t s = str_create("%s", test_symbol_str);
    obj_t* obj_symbol = memory_symbol(&memory, s);
    assert(is_symbol(obj_symbol));
    assert(str_is_equal_cstr(get_symbol(obj_symbol), test_symbol_str));

    const char* test_string_str = "test_string";
    obj_t* obj_string = memory_string(&memory, str_create("%s", test_string_str));
    assert(is_string(obj_string));
    assert(str_is_equal_cstr(get_string(obj_string), test_string_str));

    FILE* file = fopen("test.txt", "w");
    assert(file != NULL);
    obj_t* obj_file = memory_file(&memory, file);
    assert(is_file(obj_file));
    assert(get_file(obj_file) == file);
    fclose(file);

    memory_destroy(&memory);
}
