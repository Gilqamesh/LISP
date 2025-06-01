#include "universe.h"

static int backrace_full_callback(void *data, uintptr_t pc, const char *filename, int lineno, const char *function) {
    if (!filename) {
        return 1;
    }
    obj_error_t* self = (obj_error_t*) data;
    obj_string_push_cstr(self->backtrace_info, "%s '%s' %d\n", filename, function, lineno);
    return 0;
}

obj_error_t* obj_error_new(obj_string_t* message, const char* stringified_args, ...) {
    obj_error_t* self = (obj_error_t*) malloc(sizeof(obj_error_t));
    obj_init((obj_t*) self, OBJ_TYPE_ERROR);
    self->message = obj_string_new();
    self->backtrace_info = obj_string_new();

    backtrace_full(UNIVERSE.backtrace_state, 1, backrace_full_callback, NULL, self);

    obj_string_push_cstr(self->message, "\"");
    obj_string_push_string(self->message, message);
    obj_string_push_cstr(self->message, "\"");
    va_list args;
    va_start(args, stringified_args);
    while (*stringified_args) {
        if (*stringified_args == ',') {
            ++stringified_args;
            assert(*stringified_args == ' ');
            ++stringified_args;
        } else {
            int param_fill = 0;
            char param[64];
            while (param_fill + 1 < sizeof(param) && *stringified_args && *stringified_args != ',') {
                param[param_fill++] = *stringified_args++;
            }
            assert(param_fill < sizeof(param));
            param[param_fill] = '\0';
            obj_string_push_cstr(self->message, " (%s", param);
            obj_t* obj = va_arg(args, obj_t*);
            assert(obj);
            obj_string_push_cstr(self->message, " ");
            obj_to_string(obj, self->message);
            obj_string_push_cstr(self->message, ")");
        }
    }
    va_end(args);

    err_throw(self);
    return self;
}

void obj_error_delete(obj_error_t* self) {
    obj_string_delete(self->message);
    obj_string_delete(self->backtrace_info);
    free(self);
}

bool is_error(const obj_t* self) {
    return self->type == OBJ_TYPE_ERROR;
}

obj_ffi_t* obj_error_to_ffi(const obj_error_t* self) {
    assert(0 && "todo: implement");
}

void obj_error_to_string(const obj_error_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_string(str, self->message);
    obj_string_push_cstr(str, ">");
    if (obj_string_size(self->backtrace_info)) {
        obj_string_push_cstr(str, "\n");
        obj_string_push_string(str, self->backtrace_info);
    } else {
        obj_string_push_cstr(str, " (no backtrace available)");
    }
}

obj_error_t* obj_error_copy(const obj_error_t* self) {
    assert(0 && "cannot copy error objects");
}

bool obj_error_equal(const obj_error_t* self, const obj_error_t* other) {
    assert(0 && "todo: implement");
}

bool obj_error_is_truthy(const obj_error_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_error_hash(const obj_error_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_error_eval(const obj_error_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_error_apply(const obj_error_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
