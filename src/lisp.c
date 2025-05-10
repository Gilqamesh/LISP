#include "lisp.h"
#include "err.h"

static obj_t* vlist_null_terminated(memory_t* memory, va_list args);
static obj_t* apply_primitive(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* apply_compound(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static obj_t* apply_macro(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
static void obj_error_to_string(const obj_t* obj, str_t* str);
static void obj_eof_to_string(const obj_t* obj, str_t* str);
static void obj_nil_to_string(const obj_t* obj, str_t* str);
static void obj_void_to_string(const obj_t* obj, str_t* str);
static void obj_bool_to_string(const obj_t* obj, str_t* str);
static void obj_cons_to_string(const obj_t* obj, str_t* str);
static void obj_real_to_string(const obj_t* obj, str_t* str);
static void obj_symbol_to_string(const obj_t* obj, str_t* str);
static void obj_string_to_string(const obj_t* obj, str_t* str);
static void obj_file_to_string(const obj_t* obj, str_t* str);
static void obj_env_to_string(const obj_t* obj, str_t* str);
static void obj_macro_to_string(const obj_t* obj, str_t* str);
static void obj_primitive_to_string(const obj_t* obj, str_t* str);
static void obj_compound_to_string(const obj_t* obj, str_t* str);

static obj_t* vlist_null_terminated(memory_t* memory, va_list args) {
    obj_t* obj = va_arg(args, obj_t*);
    if (!obj) {
        return memory_nil(memory);
    }
    return memory_cons(memory, obj, vlist_null_terminated(memory, args));
}

static obj_t* apply_primitive(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    primitive_t primitive = get_primitive(op);
    obj_t* result = primitive(memory, op, args, env);
    return result;
}

static obj_t* apply_compound(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* params = get_compound_params(op);
    obj_t* body = get_compound_body(op);
    obj_t* captured_env = get_compound_env(op);
    obj_t* evaled_args = list_of_values(memory, args, env);
    obj_t* new_env = env_extend(memory, captured_env, params, evaled_args);
    if (is_error(new_env)) {
        return new_env;
    }
    return begin(memory, body, new_env);
}

static obj_t* apply_macro(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* params = get_macro_params(op);
    obj_t* body = get_macro_body(op);
    obj_t* new_env = env_extend(memory, env, params, args);
    if (is_error(new_env)) {
        return new_env;
    }
    return begin(memory, body, new_env);
}

static void obj_error_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<error ");
    str_push_str(str, get_error_message(obj));
    str_push(str, ">");
}

void obj_eof_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<eof>");
}

void obj_nil_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<nil>");
}

void obj_void_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<void>");
}

void obj_bool_to_string(const obj_t* obj, str_t* str) {
    str_push(str, get_bool(obj) ? "#t" : "#f");
}

void obj_cons_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "(");
    while (is_cons(obj)) {
        obj_to_string(get_car(obj), str);
        if (is_cons(get_cdr(obj))) {
            str_push(str, " ");
            obj = get_cdr(obj);
        } else if (is_nil(get_cdr(obj))) {
            break ;
        } else {
            str_push(str, " . ");
            obj_to_string(get_cdr(obj), str);
            break ;
        }
    }
    str_push(str, ")");
}

void obj_real_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "%f", get_real(obj));
}

void obj_symbol_to_string(const obj_t* obj, str_t* str) {
    str_push_str(str, get_symbol(obj));
}

void obj_string_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "\"");
    str_push_str(str, get_string(obj));
    str_push(str, "\"");
}

void obj_file_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<file>");
}

void obj_env_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<env (");
    hasher_t* bindings = get_env_bindings(obj);
    hasher_entry_t* begin = hasher_first(bindings);
    while (begin) {
        hasher_entry_t* next = hasher_next(bindings, begin);
        interned_entry_t* interned_entry = (interned_entry_t*) begin->entry;
        str_push_str(str, &interned_entry->s);
        if (next) {
            str_push(str, " ");
        }
        begin = next;
    }
    str_push(str, ")>");
}

void obj_macro_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<macro ");
    obj_to_string(get_macro_params(obj), str);
    str_push(str, " ");
    obj_to_string(get_macro_body(obj), str);
    str_push(str, ">");
}

void obj_primitive_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<primitive ");
    str_push_str(str, get_primitive_name(obj));
    str_push(str, ">");
}

void obj_compound_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<compound ");
    obj_to_string(get_compound_params(obj), str);
    str_push(str, " ");
    obj_to_string(get_compound_body(obj), str);
    str_push(str, " ");
    obj_to_string(get_compound_env(obj), str);
    str_push(str, ">");
}

obj_t* eval(memory_t* memory, obj_t* obj, obj_t* env) {
    obj_t* expanded_obj = macroexpand(memory, obj, env);
    if (is_error(expanded_obj)) {
        return expanded_obj;
    }

    obj_t* result = expanded_obj;

    if (is_symbol(expanded_obj)) {
        result = get_env_binding(memory, env, expanded_obj);
        if (!result) {
            result = err(str_create("Eval: unbound variable"), obj, expanded_obj);
        }
    } else if (is_cons(expanded_obj)) {
        obj_t* op = eval(memory, get_car(expanded_obj), env);
        obj_t* args = get_cdr(expanded_obj);
        result = apply(memory, op, args, env);
    }

    return result;
}

obj_t* apply(memory_t* memory, obj_t* op, obj_t* args, obj_t* env) {
    obj_t* result = 0;

    if (is_primitive(op)) {
        result = apply_primitive(memory, op, args, env);
    } else if (is_compound(op)) {
        result = apply_compound(memory, op, args, env);
    } else if (is_macro(op)) {
        result = apply_macro(memory, op, args, env);
        if (!is_error(result)) {
            str_t s = str();
            str_push(&s, "(op ");
            obj_to_string(op, &s);
            str_push(&s, ") (args ");
            obj_to_string(args, &s);
            str_push(&s, ") (env ");
            obj_to_string(env, &s);
            str_push(&s, ")");
            fprintf(stderr, "warning: macro applied during runtime: %s\n", str_data(&s));
            str_destroy(&s);
        }
    } else {
        result = err(str_create("Apply: invalid op"), op, args);
    }

    return result;
}

obj_t* macroexpand_1(memory_t* memory, obj_t* op, obj_t* env) {
    obj_t* start = op;
    while (is_cons(op)) {
        obj_t* operator = get_car(op);
        obj_t* args = get_cdr(op);
        if (is_cons(operator)) {
            op = operator;
        } else {
            if (is_macro(operator)) {
                obj_t* expanded = apply_macro(memory, operator, args, env);
                if (is_error(expanded)) {
                    start = expanded;
                } else {
                    if (op != start) {
                        set_car(op, expanded);
                    } else {
                        start = expanded;
                    }
                }
            } else if (is_symbol(operator)) {
                obj_t* binding = get_env_binding(memory, env, operator);
                if (binding && is_macro(binding)) {
                    obj_t* expanded = apply_macro(memory, binding, args, env);
                    if (is_error(expanded)) {
                        start = expanded;
                    } else {
                        if (op != start) {
                            set_car(op, expanded);
                        } else {
                            start = expanded;
                        }
                    }
                }
            }
            break ;
        }
    }
    return start;
}

obj_t* macroexpand(memory_t* memory, obj_t* op, obj_t* env) {
    obj_t* result = op;
    if (is_cons(result)) {
        obj_t* operator = get_car(result);
        obj_t* args = get_cdr(result);
        obj_t* expanded_operator = macroexpand(memory, operator, env);
        if (is_error(expanded_operator)) {
            return expanded_operator;
        }

        set_car(result, expanded_operator);
        if (is_macro(expanded_operator)) {
            result = apply_macro(memory, expanded_operator, args, env);
        } else if (is_symbol(expanded_operator)) {
            obj_t* binding = get_env_binding(memory, env, expanded_operator);
            if (binding && is_macro(binding)) {
                result = apply_macro(memory, binding, args, env);
            }
        }
    }

    return result;
}

void print(memory_t* memory, obj_t* obj, FILE* file) {
    if (!is_void(obj)) {
        str_t s = str();
        obj_to_string(obj, &s);
        fprintf(file, "%s\n", str_data(&s));
    }
}

obj_t* list_null_terminated(memory_t* memory, ...) {
    va_list args;
    va_start(args, memory);
    obj_t* result = vlist_null_terminated(memory, args);
    va_end(args);
    return result;
}

bool is_list(obj_t* obj) {
    while (is_cons(obj)) {
        obj = get_cdr(obj);
    }
    return is_nil(obj);
}

size_t list_length(obj_t* obj) {
    size_t length = 0;
    while (!is_nil(obj)) {
        ++length;
        obj = get_cdr(obj);
    }
    return length;
}

obj_t* list_tail(obj_t* list, size_t index) {
    obj_t* start = list;
    while (!is_nil(list) && index) {
        list = get_cdr(list);
        --index;
    }
    if (index) {
        return err(str_create("Index out of bounds"), start);
    }
    return list;
}

obj_t* list_ref(obj_t* list, size_t index) {
    return get_car(list_tail(list, index));
}

bool is_eq(obj_t* obj1, obj_t* obj2) {
    return obj1 == obj2;
}

bool is_true(obj_t* obj) {
    return !(is_false(obj));
}

bool is_false(obj_t* obj) {
    return is_nil(obj) || (is_bool(obj) && !get_bool(obj));
}

obj_t* begin(memory_t* memory, obj_t* obj, obj_t* env) {
    obj_t* result = memory_void(memory);
    while (is_cons(obj)) {
        result = eval(memory, get_car(obj), env);
        obj = get_cdr(obj);
    }
    return result;
}

obj_t* list_of_values(memory_t* memory, obj_t* args, obj_t* env) {
    if (is_nil(args)) {
        return memory_nil(memory);
    }
    return memory_cons(memory, eval(memory, get_car(args), env), list_of_values(memory, get_cdr(args), env));
}

obj_t* env_extend(memory_t* memory, obj_t* env, obj_t* params, obj_t* args) {
    obj_t* start_params = params;
    obj_t* start_args = args;
    assert(is_env(env));
    obj_t* dot = memory_symbol(memory, str_create("."));
    obj_t* result = memory_env(memory);
    set_env_parent(result, env);
    while (!is_nil(params) && !is_nil(args)) {
        if (is_eq(get_car(params), dot)) {
            params = get_cdr(params);
            define_env_binding(memory, result, get_car(params), args);
            return result;
        }
        define_env_binding(memory, result, get_car(params), get_car(args));
        params = get_cdr(params);
        args = get_cdr(args);
    }

    if (is_nil(params) && is_nil(args)) {
    } else if (is_nil(params) && !is_nil(args)) {
        result = err(str_create("Too many arguments"), start_params, start_args);
    } else if (!is_nil(params) && is_nil(args)) {
        if (is_eq(get_car(params), dot)) {
            define_env_binding(memory, result, get_car(params), memory_nil(memory));
        } else {
            result = err(str_create("Too few arguments"), start_params, start_args);
        }
    } else {
        assert(0);
    }

    return result;
}

void obj_to_string(const obj_t* obj, str_t* str) {
    switch (obj->type) {
    case OBJ_TYPE_ERROR: {
        obj_error_to_string(obj, str);
    } break ;
    case OBJ_TYPE_EOF: {
        obj_eof_to_string(obj, str);
    } break ;
    case OBJ_TYPE_NIL: {
        obj_nil_to_string(obj, str);
    } break ;
    case OBJ_TYPE_VOID: {
        obj_void_to_string(obj, str);
    } break ;
    case OBJ_TYPE_BOOL: {
        obj_bool_to_string(obj, str);
    } break ;
    case OBJ_TYPE_CONS: {
        obj_cons_to_string(obj, str);
    } break ;
    case OBJ_TYPE_REAL: {
        obj_real_to_string(obj, str);
    } break ;
    case OBJ_TYPE_SYMBOL: {
        obj_symbol_to_string(obj, str);
    } break ;
    case OBJ_TYPE_STRING: {
        obj_string_to_string(obj, str);
    } break ;
    case OBJ_TYPE_MACRO: {
        obj_macro_to_string(obj, str);
    } break ;
    case OBJ_TYPE_FILE: {
        obj_file_to_string(obj, str);
    } break ;
    case OBJ_TYPE_ENV: {
        obj_env_to_string(obj, str);
    } break ;
    case OBJ_TYPE_FUNCTION_PRIMITIVE: {
        obj_primitive_to_string(obj, str);
    } break ;
    case OBJ_TYPE_FUNCTION_COMPOUND: {
        obj_compound_to_string(obj, str);
    } break ;
    default: assert(0);
    }
}
