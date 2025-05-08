#include "memory_test.h"
#include "memory.h"

obj_t* test_primitive(obj_t* self, obj_t* args) {
    return self;
}

obj_t* test_macro(obj_t* self, obj_t* args) {
    return self;
}

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
    obj_t* obj_symbol = memory_symbol(&memory, str_create_cstr(test_symbol_str));
    assert(is_symbol(obj_symbol));
    assert(str_is_equal_cstr(get_symbol(obj_symbol), test_symbol_str));

    const char* test_string_str = "test_string";
    obj_t* obj_string = memory_string(&memory, str_create_cstr(test_string_str));
    assert(is_string(obj_string));
    assert(str_is_equal_cstr(get_string(obj_string), test_string_str));

    const char* test_primitive_str = "test_primitive";
    obj_t* obj_primitive = memory_primitive(&memory, str_create_cstr(test_primitive_str), test_primitive);
    assert(is_primitive(obj_primitive));
    assert(str_is_equal_cstr(get_primitive_name(obj_primitive), test_primitive_str));

    const char* test_macro_str = "test_macro";
    obj_t* obj_macro = memory_macro(&memory, str_create_cstr(test_macro_str), test_macro);
    assert(is_macro(obj_macro));
    assert(str_is_equal_cstr(get_macro_name(obj_macro), test_macro_str));

    FILE* file = fopen("test.txt", "w");
    assert(file != NULL);
    obj_t* obj_file = memory_file(&memory, file);
    assert(is_file(obj_file));
    assert(get_file(obj_file) == file);
    fclose(file);

    memory_destroy(&memory);
}
