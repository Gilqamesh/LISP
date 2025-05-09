#include "err.h"

static memory_t* memory = NULL;

void err_init() {
    memory = (memory_t*)malloc(sizeof(memory_t));
    memory_init(memory);
}

void err_destroy() {
    memory_destroy(memory);
    free(memory);
    memory = NULL;
}

static obj_t* verr(const char* format, va_list args) {
    str_t message = str_vcreate(format, args);
    return memory_error(memory, message);
}

static obj_t* obj_verr(obj_t* obj, const char* format, va_list args) {
    str_t err_message = str_vcreate(format, args);
    str_t message;
    obj_to_string(obj, &message);
    str_push(&err_message, ": ");
    str_push_str(&err_message, &message);
    str_destroy(&message);
    obj_t* result = memory_error(memory, err_message);
}

obj_t* err(const char* format, ...) {
    va_list args;
    va_start(args, format);
    obj_t* result = verr(format, args);
    va_end(args);
    return result;
}

obj_t* err_obj(obj_t* obj, const char* format, ...) {
    va_list args;
    va_start(args, format);
    obj_t* result = obj_verr(obj, format, args);
    va_end(args);
    return result;
}
