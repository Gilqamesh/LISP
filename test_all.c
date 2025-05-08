#include "memory_test.h"
#include "obj_test.h"
#include "str_test.h"
#include "reader_test.h"

int main() {
    memory_test();
    obj_test();
    str_test();
    reader_test();

    return 1;
}
