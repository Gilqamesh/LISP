#include "universe.h"

obj_t* obj_repl_new() {
    obj_repl_t* self = (obj_repl_t*) malloc(sizeof(obj_repl_t));
    obj_init((obj_t*) self, OBJ_TYPE_REPL);
    self->reader = obj_reader_new(obj_file_new_from_fp(stdin), obj_reader_default_reader);
    self->env = obj_env_new();
    for (size_t i = 0; i < 128; i++) {
        if (isspace(i)) {
            obj_reader_add_reader_function_char(self->reader, (char) i, obj_reader_skip_whitespaces_reader);
        }
    }
    obj_reader_add_reader_function(self->reader, "(", obj_reader_left_paren_reader);
    obj_reader_add_reader_function(self->reader, ")", obj_reader_right_paren_reader);
    obj_reader_add_reader_function(self->reader, "\"", obj_reader_double_quote_reader);
    obj_reader_add_reader_function(self->reader, "'", obj_reader_quote_reader);
    obj_reader_add_reader_function(self->reader, "`", obj_reader_backtick_reader);
    obj_reader_add_reader_function(self->reader, ",", obj_reader_comma_reader);

    obj_env_define(self->env, obj_symbol_new(obj_string_new_cstr("if")), obj_primitive_new(false, obj_primitive_if));
    obj_env_define(self->env, obj_symbol_new(obj_string_new_cstr("lambda")), obj_primitive_new(false, obj_primitive_lambda));

    return (obj_t*) self;
}

void obj_repl_delete(obj_t* self) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    obj_reader_delete(obj_repl->reader);
    free(self);
}

bool is_repl(obj_t* self) {
    return self->type == OBJ_TYPE_REPL;
}

obj_repl_t* obj_as_repl(obj_t* self) {
    if (!is_repl(self)) {
        throw(obj_string_new_cstr("expected obj_repl_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_repl_t*) self;
}

ffi_type* obj_repl_to_ffi(obj_t* self) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    assert(0 && "todo: implement");
}

void obj_repl_to_string(obj_t* self, obj_t* string) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_repl_copy(obj_t* self) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    obj_t* copy = obj_repl_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_repl_is_equal(obj_t* self, obj_t* other) {
    obj_repl_t* obj_repl_self = obj_as_repl(self);
    obj_repl_t* obj_repl_other = obj_as_repl(other);
    assert(0 && "todo: implement");
}

bool obj_repl_is_truthy(obj_t* self) {
    obj_repl_t* obj_repl = obj_as_repl(self);
  assert(0 && "todo: implement");
}

size_t obj_repl_hash(obj_t* self) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    assert(0 && "todo: implement");
}

obj_t* obj_repl_eval(obj_t* self, obj_t* env) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    obj_t* last_evaled_obj = obj_void_new();
    while (1) {
        try {
            printf("> ");
            obj_t* read_obj = obj_reader_read(obj_repl->reader);
            if (is_eof(read_obj)) {
                break ;
            }

            last_evaled_obj = obj_eval(read_obj, obj_repl->env);
            if (is_void(last_evaled_obj)) {
                continue ;
            }

            obj_t* str = obj_string_new();
            obj_to_string(last_evaled_obj, str);
            printf("%s\n", obj_string_cstr(str));
            obj_string_delete(str);
        } catch {
            obj_t* err = err_catch_context();
            obj_t* str = obj_string_new();
            obj_to_string(err, str);
            printf("%s\n", obj_string_cstr(str));
            obj_string_delete(str);
        }
    }

    return last_evaled_obj;
}

obj_t* obj_repl_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_repl_t* obj_repl = obj_as_repl(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
