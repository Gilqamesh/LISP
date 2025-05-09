#include "obj_test.h"
#include "obj.h"

void test_obj() {
    for (int i = 0; i < __OBJ_TYPE_SIZE; i++) {
        obj_t _;
        obj_init(&_, (obj_type_t)i);
        assert(type(&_) == (obj_type_t)i);
    }
}

void test_obj_error() {
    obj_error_t _;
    str_t _message = str_create("test error");
    obj_error_init(&_, _message);
    assert(is_error((obj_t*)&_));
    assert(str_is_equal_str(get_error_message((obj_t*)&_), &_message));
}

void test_obj_eof() {
    obj_eof_t _;
    obj_eof_init(&_);
    assert(is_eof((obj_t*)&_));
}

void test_obj_nil() {
    obj_nil_t _;
    obj_nil_init(&_);
    assert(is_nil((obj_t*)&_));
}

void test_obj_void() {
    obj_void_t _;
    obj_void_init(&_);
    assert(is_void((obj_t*)&_));
}

void test_obj_cons() {
    obj_cons_t _;
    obj_t* _car = (obj_t*)0x1234;
    obj_t* _cdr = (obj_t*)0x5678;
    obj_cons_init(&_, _car, _cdr);
    assert(is_cons((obj_t*)&_));
    assert(get_car((obj_t*)&_) == _car);
    assert(get_cdr((obj_t*)&_) == _cdr);
    obj_t* _new_car = (obj_t*)0x9ABC;
    obj_t* _new_cdr = (obj_t*)0xDEF0;
    set_car((obj_t*)&_, _new_car);
    set_cdr((obj_t*)&_, _new_cdr);
    assert(get_car((obj_t*)&_) == _new_car);
    assert(get_cdr((obj_t*)&_) == _new_cdr);
}

void test_obj_real() {
    obj_real_t _;
    double _real = 3.14;
    obj_real_init(&_, _real);
    assert(is_real((obj_t*)&_));
    assert(get_real((obj_t*)&_) == _real);
}

void test_obj_symbol() {
    obj_symbol_t _;
    const char* _symbol_str = "test_symbol";
    obj_symbol_init(&_, str_create("%s", _symbol_str));
    assert(is_symbol((obj_t*)&_));
    assert(str_is_equal_cstr(get_symbol((obj_t*)&_), _symbol_str));
}

void test_obj_string() {
    obj_string_t _;
    const char* _string = "test_string";
    obj_string_init(&_, str_create("%s", _string));
    assert(is_string((obj_t*)&_));
    assert(str_is_equal_cstr(get_string((obj_t*)&_), _string));
}

obj_t* primitive_test(obj_t* self, obj_t* args) {
    return args;
}

void test_obj_primitive() {
    obj_primitive_t _;
    primitive_t _primitive = primitive_test;
    const char* _primitive_name = "test_primitive";
    obj_primitive_init(&_, str_create("%s", _primitive_name), _primitive);
    assert(is_primitive((obj_t*)&_));
    assert(get_primitive((obj_t*)&_) == _primitive);
    assert(str_is_equal_cstr(get_primitive_name((obj_t*)&_), _primitive_name));
    obj_t* _args = (obj_t*)0x1234;
    obj_t* _result = _primitive((obj_t*)&_, _args);
    assert(_result == _args);
}

void test_obj_macro() {
    obj_macro_t _;
    macro_t _macro = primitive_test;
    const char* _macro_name = "test_macro";
    obj_macro_init(&_, str_create("%s", _macro_name), _macro);
    assert(is_macro((obj_t*)&_));
    assert(get_macro((obj_t*)&_) == _macro);
    assert(str_is_equal_cstr(get_macro_name((obj_t*)&_), _macro_name));
    obj_t* _args = (obj_t*)0x1234;
    obj_t* _result = _macro((obj_t*)&_, _args);
    assert(_result == _args);
}

void test_obj_file() {
    obj_file_t _;
    FILE* _file = fopen("test.txt", "w");
    assert(_file != NULL);
    obj_file_init(&_, _file);
    assert(is_file((obj_t*)&_));
    assert(get_file((obj_t*)&_) == _file);
    fclose(_file);
}

void obj_test() {
    test_obj();
    test_obj_error();
    test_obj_eof();
    test_obj_nil();
    test_obj_void();
    test_obj_cons();
    test_obj_real();
    test_obj_symbol();
    test_obj_string();
    test_obj_primitive();
    test_obj_macro();
    test_obj_file();
}
