#include "universe.h"

static int backrace_full_callback(void *data, uintptr_t pc, const char *filename, int lineno, const char *function) {
    if (!filename) {
        return 1;
    }
    obj_error_t* self = (obj_error_t*) data;
    obj_string_push_cstr(self->backtrace_info, "%s '%s' %d\n", filename, function, lineno);
    return 0;
}

obj_t* obj_error_new(obj_t* message, const char* stringified_args, ...) {
    obj_error_t* self = (obj_error_t*) malloc(sizeof(obj_error_t));
    obj_init((obj_t*) self, OBJ_TYPE_ERROR);
    self->message = message;
    self->backtrace_info = obj_string_new();

    backtrace_full(UNIVERSE.backtrace_state, 1, backrace_full_callback, NULL, self);

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
    return (obj_t*) self;
}

void obj_error_delete(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    obj_string_delete(obj_error->message);
    obj_string_delete(obj_error->backtrace_info);
    free(self);
}

bool is_error(obj_t* self) {
    return self->type == OBJ_TYPE_ERROR;
}

obj_error_t* obj_as_error(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    return (obj_error_t*) self;
}

ffi_type* obj_error_to_ffi(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    assert(0 && "todo: implement");
}

void obj_error_to_string(obj_t* self, obj_t* string) {
    obj_error_t* obj_error = obj_as_error(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    obj_string_push_string(string, obj_error->message);
    obj_string_push_cstr(string, ">");
    if (obj_string_size(obj_error->backtrace_info)) {
        obj_string_push_cstr(string, "\n");
        obj_string_push_string(string, obj_error->backtrace_info);
    } else {
        obj_string_push_cstr(string, " (no backtrace available)");
    }
}

obj_t* obj_error_copy(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    assert(0 && "cannot copy error objects");
}

bool obj_error_is_equal(obj_t* self, obj_t* other) {
    obj_error_t* error_self = obj_as_error(self);
    obj_error_t* error_other = obj_as_error(other);
    assert(0 && "todo: implement");
}

bool obj_error_is_truthy(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    assert(0 && "todo: implement");
}

size_t obj_error_hash(obj_t* self) {
    obj_error_t* obj_error = obj_as_error(self);
    assert(0 && "todo: implement");
}

obj_t* obj_error_eval(obj_t* self, obj_t* env) {
    obj_error_t* obj_error = obj_as_error(self);
    return self;
}

obj_t* obj_error_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_error_t* obj_error = obj_as_error(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
