#include "repl.h"

#include "lisp.h"
#include "err.h"

static obj_t* primitive_define(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_quote(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macroexpand(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macroexpand_1(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macro(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_lambda(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_if(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_car(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_cdr(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_eq(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);

static void register_primitives(repl_t* self);

static obj_t* primitive_define(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* name = list_ref(args, 0);
    if (!is_symbol(name)) {
        return err(str_create("define: first argument must be a symbol"), name);
    }
    obj_t* value = list_ref(args, 1);
    obj_t* evaluated_value = eval(memory, value, env);
    if (is_error(evaluated_value)) {
        return evaluated_value;
    }
    obj_t* result = define_env_binding(memory, env, name, evaluated_value);
    return result;
}

static obj_t* primitive_quote(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* quoted_obj = list_ref(args, 0);
    return quoted_obj;
}

static obj_t* primitive_macroexpand(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* evaluated_arg = eval(memory, list_ref(args, 0), env);
    obj_t* expanded_obj = macroexpand(memory, evaluated_arg, env);
    return expanded_obj;
}

static obj_t* primitive_macroexpand_1(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* evaluated_arg = eval(memory, list_ref(args, 0), env);
    obj_t* expanded_obj = macroexpand_1(memory, evaluated_arg, env);
    return expanded_obj;
}

static obj_t* primitive_macro(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    // (macro (params) body ...)
    return memory_macro(memory, list_ref(args, 0), list_tail(args, 1));
}

static obj_t* primitive_lambda(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    // (lambda (params) body ...)
    return memory_compound(memory, list_ref(args, 0), list_tail(args, 1), env);
}

static obj_t* primitive_if(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    // (if test then else)
    obj_t* condition = eval(memory, list_ref(args, 0), env);
    if (is_error(condition)) {
        return condition;
    }

    if (is_true(condition)) {
        obj_t* consequence = eval(memory, list_ref(args, 1), env);
        return consequence;
    }

    obj_t* tail = list_tail(args, 2);
    if (!is_nil(tail)) {
        obj_t* alternative = eval(memory, get_car(tail), env);
        return alternative;
    }

    return memory_void(memory);
}

static obj_t* primitive_car(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    return get_car(list_ref(args, 0));
}

static obj_t* primitive_cdr(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    return get_cdr(list_ref(args, 0));
}

static obj_t* primitive_eq(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(memory, arg1, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    obj_t* evaled_arg2 = eval(memory, arg2, env);
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }
    if (is_eq(evaled_arg1, evaled_arg2)) {
        return memory_bool(memory, true);
    }
    return memory_bool(memory, false);
}

static void register_primitives(repl_t* self) {
#define _REGISTER_PRIMITIVE(name, fn) do { \
    define_env_binding(&self->memory, self->env, memory_symbol(&self->memory, str_create(name)), \
                       memory_primitive(&self->memory, str_create(name), fn)); \
} while (0)
    _REGISTER_PRIMITIVE("define", &primitive_define);
    _REGISTER_PRIMITIVE("quote", &primitive_quote);
    _REGISTER_PRIMITIVE("macroexpand", &primitive_macroexpand);
    _REGISTER_PRIMITIVE("macroexpand-1", &primitive_macroexpand_1);
    _REGISTER_PRIMITIVE("macro", &primitive_macro);
    _REGISTER_PRIMITIVE("lambda", &primitive_lambda);
    _REGISTER_PRIMITIVE("if", &primitive_if);
    _REGISTER_PRIMITIVE("car", &primitive_car);
    _REGISTER_PRIMITIVE("cdr", &primitive_cdr);
    _REGISTER_PRIMITIVE("eq?", &primitive_eq);
#undef _REGISTER_PRIMITIVE
} 

void repl_init(repl_t* self) {
    err_init();

    memory_init(&self->memory);
    reader_init(&self->reader, &self->memory);
    reader_register_reader_macros(&self->reader);
    self->env = memory_env(&self->memory);

    register_primitives(self);
}

void repl_destroy(repl_t* self) {
    reader_destroy(&self->reader);
    memory_destroy(&self->memory);
    err_destroy();
}

void repl_run(repl_t* self) {
    while (1) {
        printf("> ");
        obj_t* read_obj = reader_read(&self->reader, stdin);
        if (is_eof(read_obj)) {
            break ;
        }

        obj_t* evaled_obj = eval(&self->memory, read_obj, self->env);

        print(&self->memory, evaled_obj, stdout);
    }
}
