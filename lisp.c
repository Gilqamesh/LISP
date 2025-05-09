#include "lisp.h"
#include "err.h"

static obj_t* vlist(memory_t* memory, va_list args) {
    obj_t* car = va_arg(args, obj_t*);
    if (!car) {
        return memory_nil(memory);
    }
    return memory_cons(memory, va_arg(args, obj_t*), vlist(memory, args));
}

obj_t* list_null_terminated(memory_t* memory, ...) {
    va_list args;
    va_start(args, memory);

    obj_t* result = vlist(memory, args);

    va_end(args);
    return result;
}

bool is_list(obj_t* obj) {
    while (is_cons(obj)) {
        obj = get_cdr(obj);
    }
    return is_nil(obj);
}

size_t list_length(obj_t* obj) {
    size_t length = 0;
    while (!is_nil(obj)) {
        ++length;
        obj = get_cdr(obj);
    }
    return length;
}

obj_t* list_tail(obj_t* list, size_t index) {
    obj_t* start = list;
    while (!is_nil(list) && index) {
        list = get_cdr(list);
        --index;
    }
    if (index) {
        return err_obj(start, "Index out of bounds");
    }
    return list;
}

obj_t* list_ref(obj_t* list, size_t index) {
    return get_car(list_tail(list, index));
}

bool is_eq(obj_t* obj1, obj_t* obj2) {
    return obj1 == obj2;
}
