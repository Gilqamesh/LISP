#include "err.h"
#include "lisp.h"

static memory_t* memory = NULL;

static obj_t* verr_null_terminated(memory_t* memory, const char* stringified_params, str_t message, va_list args);

void err_init() {
    memory = (memory_t*)malloc(sizeof(memory_t));
    memory_init(memory);
}

void err_destroy() {
    memory_destroy(memory);
    free(memory);
    memory = NULL;
}

static obj_t* verr_null_terminated(memory_t* memory, const char* stringified_params, str_t message, va_list args) {
    str_t formatted_message = str();
    str_push(&formatted_message, "\"");
    str_push_str(&formatted_message, &message);
    str_push(&formatted_message, "\"");
    while (*stringified_params) {
        if (*stringified_params == ',') {
            ++stringified_params;
            assert(*stringified_params == ' ');
            ++stringified_params;
        } else {
            int param_fill = 0;
            char param[64];
            while (param_fill + 1 < sizeof(param) && *stringified_params && *stringified_params != ',') {
                param[param_fill++] = *stringified_params++;
            }
            assert(param_fill < sizeof(param));
            param[param_fill] = '\0';
            str_push(&formatted_message, " (%s", param);
            obj_t* obj = va_arg(args, obj_t*);
            assert(obj);
            str_push(&formatted_message, " ");
            obj_to_string(obj, &formatted_message);
            str_push(&formatted_message, ")");
        }
    }
    return memory_error(memory, formatted_message);
}

obj_t* err_null_terminated(str_t message, const char* stringified_params, ...) {
    va_list args;
    va_start(args, stringified_params);
    obj_t* result = verr_null_terminated(memory, stringified_params, message, args);
    va_end(args);
    return result;
}
