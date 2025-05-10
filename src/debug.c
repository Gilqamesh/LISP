#include "debug.h"
#include "lisp.h"

const char* to_string(obj_t* obj) {
    str_t s = str();
    obj_to_string(obj, &s);
    return str_data(&s);
}
