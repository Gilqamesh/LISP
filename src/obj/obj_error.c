#include "universe.h"

obj_error_t* obj_error_new(obj_string_t* message, const char* caller, const char* stringified_args, ...) {
    obj_error_t* self = (obj_error_t*) malloc(sizeof(obj_error_t));
    obj_init((obj_t*) self, OBJ_TYPE_ERROR);
    va_list args;
    va_start(args, stringified_args);
    self->message = obj_string_new();
    obj_string_push_cstr(self->message, "\"");
    obj_string_push_string(self->message, message);
    obj_string_push_cstr(self->message, "\"");
    obj_string_push_cstr(self->message, " [in '");
    obj_string_push_cstr(self->message, caller);
    obj_string_push_cstr(self->message, "']");
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
    free(self);
}

bool is_error(const obj_t* self) {
    return self->type == OBJ_TYPE_ERROR;
}

obj_ffi_t* obj_error_to_ffi(const obj_error_t* self) {
    assert(0 && "todo: implement");
}

void obj_error_to_string(const obj_error_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<error ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_string(str, self->message);
    obj_string_push_cstr(str, ">");
}

obj_t* obj_error_copy(const obj_error_t* self) {
    assert(0 && "cannot copy error objects");
}

bool obj_error_equal(const obj_error_t* self, const obj_error_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_error_hash(const obj_error_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_error_eval(const obj_error_t* self, obj_hash_table_t* env) {
    return (obj_t*) self;
}

obj_t* obj_error_apply(const obj_error_t* self, obj_array_t* args, obj_hash_table_t* env) {
    assert(0 && "todo: implement");
}
