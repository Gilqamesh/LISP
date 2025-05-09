#include "lisp_test.h"
#include "lisp.h"

void lisp_test() {
    memory_t memory;
    memory_init(&memory);

    obj_t* obj_eof = memory_eof(&memory);
    obj_t* obj_nil = memory_nil(&memory);
    obj_t* obj_void = memory_void(&memory);

    obj_t* obj_list = list(&memory, obj_eof, obj_nil, obj_void);
    assert(is_list(obj_list));
    assert(list_length(obj_list) == 3);
    assert(is_eq(list_ref(obj_list, 0), obj_eof));
    assert(is_eq(list_ref(obj_list, 1), obj_nil));
    assert(is_eq(list_ref(obj_list, 2), obj_void));

    memory_destroy(&memory);
}
