#include "reader_test.h"
#include "reader.h"
#include "lisp.h"

void test_reader(reader_t* reader) {
    reader_register_reader_macros(reader);

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
