#include "universe.h"

static void obj_reader_skip_whitespaces(obj_reader_t* self);

static obj_t* default_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* skip_whitespaces_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* left_paren_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* right_paren_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* double_quote_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* quote_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* backtick_reader(obj_reader_t* self, obj_string_t* lexeme);
static obj_t* comma_reader(obj_reader_t* self, obj_string_t* lexeme);

static obj_t* if_primitive(const obj_primitive_t* self, obj_t* args, obj_env_t* env);
static obj_t* lambda_primitive(const obj_primitive_t* self, obj_t* args, obj_env_t* env);

static void obj_reader_skip_whitespaces(obj_reader_t* self) {
    while (!obj_file_is_at_end(self->file) && isspace(obj_file_peek_char(self->file))) {
        obj_file_read_char(self->file);
    }
}

static obj_t* default_reader(obj_reader_t* self, obj_string_t* lexeme) {
    obj_t* result = NULL;

    const size_t lexeme_size = obj_string_size(lexeme);
    if (obj_string_size(lexeme) == 0) {
        obj_string_delete(lexeme);
        result = (obj_t*) obj_void_new();
    } else if ((obj_string_at(lexeme, 0) == '.' && 1 < lexeme_size) || isdigit(obj_string_at(lexeme, 0))) {
        bool had_dot = false;
        for (size_t i = 0; result == NULL && i < lexeme_size; ++i) {
            char c = obj_string_at(lexeme, i);
            if (c == '.') {
                if (!had_dot) {
                    had_dot = true;
                } else {
                    result = (obj_t*) obj_symbol_new(lexeme);
                }
            } else if (isdigit(c)) {
            } else {
                result = (obj_t*) obj_symbol_new(lexeme);
            }
        }

        if (result == NULL) {
            const double epsilon = 1e-6;
            double r64 = atof(obj_string_cstr(lexeme));
            float r32 = r64;
            int64_t i64 = r64;
            int32_t i32 = r64;
            if (r64 == (double) i32) {
                result = (obj_t*) obj_i32_new(i32);
            } else if (r64 == (double) i64) {
                result = (obj_t*) obj_i64_new(i64);
            } else if (fabs(r64 - (double) r32) < epsilon) {
                result = (obj_t*) obj_r32_new(r32);
            } else {
                result = (obj_t*) obj_r64_new(r64);
            }
            obj_string_delete(lexeme);
        }
    } else {
        result = (obj_t*) obj_symbol_new(lexeme);
    }

    return result;
}

static obj_t* skip_whitespaces_reader(obj_reader_t* self, obj_string_t* lexeme) {
    obj_reader_skip_whitespaces(self);
    obj_string_delete(lexeme);
    return (obj_t*) obj_void_new();
}

static obj_t* left_paren_reader(obj_reader_t* self, obj_string_t* lexeme) {
    obj_t* result = NULL;
    obj_t** head = &result;
    while (!obj_file_is_at_end(self->file)) {
        obj_reader_skip_whitespaces(self);
        if (obj_file_is_at_end(self->file)) {
            break ;
        }
        switch (obj_file_peek_char(self->file)) {
        case ')': {
            obj_file_read_char(self->file);
            obj_string_delete(lexeme);
            *head = (obj_t*) obj_void_new();
            return result;
        } break ;
        default: {
            *head = (obj_t*) obj_cons_new(obj_reader_read(self), NULL);
            head = &((*(obj_cons_t**) head)->cdr);
        } break ;
        }
    }
    throw(obj_string_new_cstr("unmatched left parenthesis"), (obj_t*) self);
}

static obj_t* right_paren_reader(obj_reader_t* self, obj_string_t* lexeme) {
    throw(obj_string_new_cstr("unmatched right parenthesis"), (obj_t*) self, lexeme);
}

static obj_t* double_quote_reader(obj_reader_t* self, obj_string_t* lexeme) {
    while (!obj_file_is_at_end(self->file)) {
        char c = obj_file_read_char(self->file);
        if (c == '"') {
            return (obj_t*) lexeme;
        }
        obj_string_push_cstr(lexeme, "%c", c);
    }
    throw(obj_string_new_cstr("unterminated string literal"), (obj_t*) self, lexeme);
}

static obj_t* quote_reader(obj_reader_t* self, obj_string_t* lexeme) {
    obj_string_delete(lexeme);
    return (obj_t*) obj_cons_new((obj_t*) obj_symbol_new(obj_string_new_cstr("quote")), obj_reader_read(self));
}

static obj_t* backtick_reader(obj_reader_t* self, obj_string_t* lexeme) {
    obj_string_delete(lexeme);
    return (obj_t*) obj_cons_new((obj_t*) obj_symbol_new(obj_string_new_cstr("quasiquote")), obj_reader_read(self));
}

static obj_t* comma_reader(obj_reader_t* self, obj_string_t* lexeme) {
    if (obj_file_is_at_end(self->file)) {
        throw(obj_string_new_cstr("unexpected end of file after ','"), (obj_t*) self);
    }
    switch (obj_file_read_char(self->file)) {
    case '@': {
        return (obj_t*) obj_cons_new((obj_t*) obj_symbol_new(obj_string_new_cstr("unquote-splicing")), obj_reader_read(self));
    } break ;
    default: {
        return (obj_t*) obj_cons_new((obj_t*) obj_symbol_new(obj_string_new_cstr("unquote")), obj_reader_read(self));
    }
    }
}

static obj_t* if_primitive(const obj_primitive_t* self, obj_t* args, obj_env_t* env) {
    obj_t* evaled_condition = obj_eval(obj_cons_ref(args, 0), env);
    if (obj_is_truthy(evaled_condition)) {
        return obj_eval(obj_cons_ref(args, 1), env);
    } else {
        obj_t* tail = obj_cons_tail(args, 1);
        if (is_cons(tail)) {
            return obj_eval(((obj_cons_t*) tail)->car, env);
        } else {
            return (obj_t*) obj_void_new();
        }
    }
}

static obj_t* lambda_primitive(const obj_primitive_t* self, obj_t* args, obj_env_t* env) {
    return (obj_t*) obj_closure_new(obj_cons_ref(args, 0), obj_cons_ref(args, 1), env);
}

obj_repl_t* obj_repl_new() {
    obj_repl_t* self = (obj_repl_t*) malloc(sizeof(obj_repl_t));
    obj_init((obj_t*) self, OBJ_TYPE_REPL);
    self->reader = obj_reader_new(obj_file_new_from_fp(stdin), default_reader);
    self->env = obj_env_new();
    for (size_t i = 0; i < 128; i++) {
        if (isspace(i)) {
            obj_reader_add_reader_function_char(self->reader, (char) i, skip_whitespaces_reader);
        }
    }
    obj_reader_add_reader_function(self->reader, "(", left_paren_reader);
    obj_reader_add_reader_function(self->reader, ")", right_paren_reader);
    obj_reader_add_reader_function(self->reader, "\"", double_quote_reader);
    obj_reader_add_reader_function(self->reader, "'", quote_reader);
    obj_reader_add_reader_function(self->reader, "`", backtick_reader);
    obj_reader_add_reader_function(self->reader, ",", comma_reader);

    obj_env_define(self->env, (obj_t*) obj_symbol_new(obj_string_new_cstr("if")), (obj_t*) obj_primitive_new(false, if_primitive));
    obj_env_define(self->env, (obj_t*) obj_symbol_new(obj_string_new_cstr("lambda")), (obj_t*) obj_primitive_new(false, lambda_primitive));

    return self;
}

void obj_repl_delete(obj_repl_t* self) {
    obj_reader_delete(self->reader);
    free(self);
}

bool is_repl(const obj_t* self) {
    return self->type == OBJ_TYPE_REPL;
}

obj_ffi_t* obj_repl_to_ffi(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

void obj_repl_to_string(const obj_repl_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_repl_t* obj_repl_copy(const obj_repl_t* self) {
    obj_repl_t* copy = obj_repl_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_repl_equal(const obj_repl_t* self, const obj_repl_t* other) {
    assert(0 && "todo: implement");
}

bool obj_repl_is_truthy(const obj_repl_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_repl_hash(const obj_repl_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_repl_eval(const obj_repl_t* self, obj_env_t* env) {
    obj_t* last_evaled_obj = (obj_t*) obj_void_new();
    while (1) {
        try {
            printf("> ");
            obj_t* read_obj = obj_reader_read(self->reader);
            if (is_eof(read_obj)) {
                break ;
            }

            last_evaled_obj = obj_eval(read_obj, self->env);
            if (is_void(last_evaled_obj)) {
                continue ;
            }

            obj_string_t* str = obj_string_new();
            obj_to_string(last_evaled_obj, str);
            printf("%s\n", obj_string_cstr(str));
            obj_string_delete(str);
        } catch {
            obj_t* err = (obj_t*) err_catch_context();
            obj_string_t* str = obj_string_new();
            obj_to_string(err, str);
            printf("%s\n", obj_string_cstr(str));
            obj_string_delete(str);
        }
    }

    return last_evaled_obj;
}

obj_t* obj_repl_apply(const obj_repl_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}
