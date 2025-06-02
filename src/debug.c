#include "debug.h"
#include "universe.h"

const char* to_string(obj_t* obj) {
    obj_t* string = obj_string_new();
    obj_to_string(obj, string);
    const char* result = obj_string_cstr(string);
    return result;
}
