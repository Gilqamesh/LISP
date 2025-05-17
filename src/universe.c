#include "universe.h"

#include <dlfcn.h>

universe_t UNIVERSE;

static obj_t* primitive_define(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_set(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_quote(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macroexpand(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macroexpand_1(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_macro(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_lambda(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_if(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_car(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_cdr(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_set_car(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_set_cdr(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_eq(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_read(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_write(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_eval(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_apply(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_fopen(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_ffi(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_dlsym(obj_t* op, obj_t* args, obj_t* env);
static obj_t* primitive_ffi_call(obj_t* op, obj_t* args, obj_t* env);

static obj_t* vlist_null_terminated(va_list args);
static obj_t* apply_primitive(obj_t* op, obj_t* args, obj_t* env);
static obj_t* apply_compound(obj_t* op, obj_t* args, obj_t* env);
static obj_t* apply_macro(obj_t* op, obj_t* args, obj_t* env);
static void obj_lisp_type_to_string(const obj_t* obj, str_t* str);
static void obj_error_to_string(const obj_t* obj, str_t* str);
static void obj_eof_to_string(const obj_t* obj, str_t* str);
static void obj_nil_to_string(const obj_t* obj, str_t* str);
static void obj_void_to_string(const obj_t* obj, str_t* str);
static void obj_pointer_to_string(const obj_t* obj, str_t* str);
static void obj_bool_to_string(const obj_t* obj, str_t* str);
static void obj_cons_to_string(const obj_t* obj, str_t* str);
static void obj_real_to_string(const obj_t* obj, str_t* str);
static void obj_symbol_to_string(const obj_t* obj, str_t* str);
static void obj_string_to_string(const obj_t* obj, str_t* str);
static void obj_file_to_string(const obj_t* obj, str_t* str);
static void obj_env_to_string(const obj_t* obj, str_t* str);
static void obj_ffi_to_string(const obj_t* obj, str_t* str);
static void obj_macro_to_string(const obj_t* obj, str_t* str);
static void obj_primitive_to_string(const obj_t* obj, str_t* str);
static void obj_compound_to_string(const obj_t* obj, str_t* str);
static void obj_to_string(const obj_t* obj, str_t* str);

static void* ffi_get_internal_data_from_type(ffi_type* type, obj_t* obj);

static obj_t* eval(obj_t* obj, obj_t* env);
static obj_t* apply(obj_t* op, obj_t* args, obj_t* env);
static obj_t* macroexpand(obj_t* op, obj_t* env);
static obj_t* macroexpand_1(obj_t* op, obj_t* env);
static void print(obj_t* obj, FILE* file);

static obj_t* list_null_terminated(universe_t* universe, ...);
// ex. usage: list(obj1, obj2, obj3)
# define list(...) list_null_terminated(&UNIVERSE, __VA_ARGS__, 0)

static bool is_list(obj_t* obj);
static size_t list_length(obj_t* obj);
static obj_t* list_tail(obj_t* list, size_t index);
static obj_t* list_ref(obj_t* list, size_t index);

static bool is_eq(obj_t* obj1, obj_t* obj2);
static bool is_true(obj_t* obj);
static bool is_false(obj_t* obj);

static obj_t* begin(obj_t* obj, obj_t* env);

static obj_t* list_of_values(obj_t* args, obj_t* env);

static obj_t* env_extend(obj_t* env, obj_t* params, obj_t* args);

static obj_t* err_null_terminated(str_t message, const char* stringified_params, ...);
// ex. usage: err(memory, obj1, obj2, obj3)
# define err(message, ...) err_null_terminated(message, #__VA_ARGS__, __VA_ARGS__, 0)
static obj_t* verr_null_terminated(const char* stringified_params, str_t message, va_list args);

static obj_t* get_env_binding(obj_t* obj, obj_t* key);
static obj_t* set_env_binding(obj_t* obj, obj_t* key, obj_t* value);
static obj_t* define_env_binding(obj_t* obj, obj_t* key, obj_t* value);

static size_t interned_entries_key_hash(const void* key);
static int interned_entries_key_compare(const void* key1, const void* key2);
static const void* interned_entries_entry_key(const void* entry);
static interned_entry_t* interned_entries_insert(str_t s, obj_t* obj);
static void interned_entries_remove(size_t index);

static obj_t* memory_type(obj_type_t type);
static obj_t* memory_error(str_t message);
static obj_t* memory_eof();
static obj_t* memory_nil();
static obj_t* memory_void();
static obj_t* memory_pointer(void* pointer);
static obj_t* memory_bool(bool boolean);
static obj_t* memory_cons(obj_t* car, obj_t* cdr);
static obj_t* memory_real(double real);
static obj_t* memory_symbol(str_t symbol);
static obj_t* memory_string(str_t string);
static obj_t* memory_file(FILE* file);
static obj_t* memory_env();
static obj_t* memory_ffi();
static obj_t* memory_macro(obj_t* params, obj_t* body);
static obj_t* memory_primitive(str_t name, primitive_t primitive);
static obj_t* memory_compound(obj_t* params, obj_t* body, obj_t* env);

static obj_t* memory_from_data(void* data, obj_type_t type);

typedef obj_t* (*reader_function_t)(FILE* file);

static void reader_node_init(reader_node_t* self);
static void reader_node_destroy(reader_node_t* self);

static void reader_register_reader_macro_str(const char* name, reader_function_t reader_function);
static void reader_register_reader_macro_char(char c, reader_function_t reader_function);

static char reader_peek(FILE* file);
static char reader_getc(FILE* file);
static void reader_ungetc(FILE* file, char c);
static bool reader_is_at_end(FILE* file);
static bool reader_is_whitespace(char c);

static obj_t* reader_read(FILE* file);

static obj_t* reader_skip_whitespaces(FILE* file);
static obj_t* reader_double_quote(FILE* file);
static obj_t* reader_quote(FILE* file);
static obj_t* reader_qauasiquote(FILE* file);
static obj_t* reader_comma(FILE* file);
static obj_t* reader_right_parent(FILE* file);
static obj_t* reader_left_parent(FILE* file);
static obj_t* reader_true(FILE* file);
static obj_t* reader_false(FILE* file);
static obj_t* reader_multiline_comment(FILE* file);

static obj_t* primitive_define(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* name = list_ref(args, 0);
    if (!is_symbol(name)) {
        return err(str_create("define: first argument must be a symbol"), name);
    }
    obj_t* value = list_ref(args, 1);
    obj_t* evaluated_value = eval(value, env);
    if (is_error(evaluated_value)) {
        return evaluated_value;
    }
    obj_t* result = define_env_binding(env, name, evaluated_value);
    return result;
}

static obj_t* primitive_set(obj_t* op, obj_t* args, obj_t* env) {
    // (set! name value)
    obj_t* name = list_ref(args, 0);
    if (!is_symbol(name)) {
        return err(str_create("set!: first argument must be a symbol"), name);
    }
    obj_t* value = list_ref(args, 1);
    obj_t* evaluated_value = eval(value, env);
    if (is_error(evaluated_value)) {
        return evaluated_value;
    }
    obj_t* result = set_env_binding(env, name, evaluated_value);
    return result;
}

static obj_t* primitive_quote(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* quoted_obj = list_ref(args, 0);
    return quoted_obj;
}

static obj_t* primitive_macroexpand(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* evaluated_arg = eval(list_ref(args, 0), env);
    obj_t* expanded_obj = macroexpand(evaluated_arg, env);
    return expanded_obj;
}

static obj_t* primitive_macroexpand_1(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* evaluated_arg = eval(list_ref(args, 0), env);
    obj_t* expanded_obj = macroexpand_1(evaluated_arg, env);
    return expanded_obj;
}

static obj_t* primitive_macro(obj_t* op, obj_t* args, obj_t* env) {
    // (macro (params) body ...)
    return memory_macro(list_ref(args, 0), list_tail(args, 1));
}

static obj_t* primitive_lambda(obj_t* op, obj_t* args, obj_t* env) {
    // (lambda (params) body ...)
    return memory_compound(list_ref(args, 0), list_tail(args, 1), env);
}

static obj_t* primitive_if(obj_t* op, obj_t* args, obj_t* env) {
    // (if test then else)
    obj_t* condition = eval(list_ref(args, 0), env);
    if (is_error(condition)) {
        return condition;
    }

    if (is_true(condition)) {
        obj_t* consequence = eval(list_ref(args, 1), env);
        return consequence;
    }

    obj_t* tail = list_tail(args, 2);
    if (!is_nil(tail)) {
        obj_t* alternative = eval(get_car(tail), env);
        return alternative;
    }

    return memory_void();
}

static obj_t* primitive_car(obj_t* op, obj_t* args, obj_t* env) {
    return get_car(list_ref(args, 0));
}

static obj_t* primitive_cdr(obj_t* op, obj_t* args, obj_t* env) {
    return get_cdr(list_ref(args, 0));
}

static obj_t* primitive_set_car(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(arg1, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    if (!is_cons(evaled_arg1)) {
        return err(str_create("set-car!: first argument must be a cons cell"), evaled_arg1);
    }
    obj_t* evaled_arg2 = eval(arg2, env);
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }
    set_car(evaled_arg1, evaled_arg2);
    return evaled_arg2;
}

static obj_t* primitive_set_cdr(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(arg1, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    if (!is_cons(evaled_arg1)) {
        return err(str_create("set-car!: first argument must be a cons cell"), evaled_arg1);
    }
    obj_t* evaled_arg2 = eval(arg2, env);
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }
    set_cdr(evaled_arg1, evaled_arg2);
    return evaled_arg2;
}

static obj_t* primitive_eq(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(arg1, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    obj_t* evaled_arg2 = eval(arg2, env);
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }
    if (is_eq(evaled_arg1, evaled_arg2)) {
        return memory_bool(true);
    }
    return memory_bool(false);
}

static obj_t* primitive_read(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg = list_ref(args, 0);
    obj_t* evaled_arg = eval(arg, env);
    if (is_error(evaled_arg)) {
        return evaled_arg;
    }
    if (!is_file(evaled_arg)) {
        return err(str_create("read: first argument must be a file"), evaled_arg);
    }

    FILE* file = get_file(evaled_arg);
    return reader_read(file);
}

static obj_t* primitive_write(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(arg1, env);
    obj_t* evaled_arg2 = eval(arg2, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    if (!is_file(evaled_arg1)) {
        return err(str_create("write: second argument must be a file"), evaled_arg1);
    }
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }

    FILE* file = get_file(evaled_arg1);
    str_t s = str();
    obj_to_string(evaled_arg2, &s);
    int written = fprintf(get_file(evaled_arg1), "%s\n", str_data(&s));
    if (written < 0) {
        return err(str_create("write: error writing to file"), evaled_arg1);
    }
    size_t expected = str_size(&s);
    str_destroy(&s);
    return memory_string(str_create("write: written %d, expected %d", written, expected));
}

static obj_t* primitive_eval(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg = list_ref(args, 0);
    obj_t* evaled_arg = eval(arg, env);
    return eval(evaled_arg, env);
}

static obj_t* primitive_apply(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = list_ref(args, 0);
    obj_t* arg2 = list_ref(args, 1);
    obj_t* evaled_arg1 = eval(arg1, env);
    obj_t* evaled_arg2 = eval(arg2, env);
    if (is_error(evaled_arg1)) {
        return evaled_arg1;
    }
    if (is_error(evaled_arg2)) {
        return evaled_arg2;
    }
    return apply(evaled_arg1, evaled_arg2, env);
}

static obj_t* primitive_fopen(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg1 = get_car(args);
    args = get_cdr(args);
    if (is_nil(args)) {
        return err(str_create("fopen: missing arguments"), arg1);
    }
    obj_t* arg2  = get_car(args);
    obj_t* path = eval(arg1, env);
    obj_t* mode = eval(arg2, env);
    if (is_error(path)) {
        return path;
    }
    if (is_error(mode)) {
        return mode;
    }
    if (!is_string(path)) {
        return err(str_create("fopen: first argument must be a string"), path);
    }
    if (!is_string(mode)) {
        return err(str_create("fopen: second argument must be a string"), mode);
    }
    const str_t* filename = get_string(path);
    FILE* file = fopen(str_data(filename), str_data(get_string(mode)));
    if (!file) {
        return err(str_create("fopen: error opening file"), path, mode);
    }
    return memory_file(file);
}

static obj_t* primitive_ffi(obj_t* op, obj_t* args, obj_t* env) {
    // (ffi return-type ... arg-types)
    // alternatively this could be a wrapper for the call where the user could install pre/postamble code
    if (is_nil(args)) {
        return err(str_create("ffi: missing arguments"), args);
    }
    obj_t* arg1 = get_car(args);
    obj_t* return_type = eval(arg1, env);
    if (is_error(return_type)) {
        return return_type;
    }
    if (!is_lisp_type(return_type)) {
        return err(str_create("ffi: first argument must be a lisp type"), return_type);
    }
    args = get_cdr(args);
    if (is_nil(args)) {
        return err(str_create("ffi: missing arguments"), return_type);
    }

    obj_t* ffi = memory_ffi();
    set_ffi_ret_type(ffi, get_lisp_type(return_type));
    while (!is_nil(args)) {
        obj_t* arg = get_car(args);
        obj_t* evaled_arg = eval(arg, env);
        if (is_error(evaled_arg)) {
            return evaled_arg;
        }
        if (!is_lisp_type(evaled_arg)) {
            return err(str_create("ffi: argument must be a lisp type"), evaled_arg);
        }
        add_ffi_arg_type(ffi, get_lisp_type(evaled_arg));
        args = get_cdr(args);
    }
    obj_ffi_finalize(ffi);
    return ffi;
}

static obj_t* primitive_dlsym(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* arg = get_car(args);
    obj_t* evaled_arg = eval(arg, env);
    if (is_error(evaled_arg)) {
        return evaled_arg;
    }
    if (!is_string(evaled_arg)) {
        return err(str_create("dlsym: first argument must be a string"), evaled_arg);
    }

    void* p = dlsym(UNIVERSE.dlhandle, str_data(get_string(evaled_arg)));
    if (!p) {
        return err(str_create("dlsym: error loading symbol"), evaled_arg);
    }
    return memory_pointer(p);
}

static obj_t* primitive_ffi_call(obj_t* op, obj_t* args, obj_t* env) {
    // (ffi-call ffi fn-ptr ... args)
    if (is_nil(args)) {
        return err(str_create("ffi-call: missing arguments"), args);
    }
    obj_t* arg1 = get_car(args);
    obj_t* ffi = eval(arg1, env);
    if (is_error(ffi)) {
        return ffi;
    }
    if (!is_ffi(ffi)) {
        return err(str_create("ffi-call: first argument must be a ffi object"), ffi);
    }
    args = get_cdr(args);
    if (is_nil(args)) {
        return err(str_create("ffi-call: missing arguments"), ffi);
    }
    obj_t* arg2 = get_car(args);
    obj_t* pointer = eval(arg2, env);
    if (is_error(pointer)) {
        return pointer;
    }
    if (!is_pointer(pointer)) {
        return err(str_create("ffi-call: second argument must be a pointer"), pointer);
    }
    args = get_cdr(args);
    if (is_nil(args)) {
        return err(str_create("ffi-call: missing arguments"), pointer);
    }

    obj_ffi_t* obj_ffi = (obj_ffi_t*)ffi;
    void* converted_args[16];
    for (int i = 0; i < obj_ffi->arg_types_top; ++i) {
        if (is_nil(args)) {
            return err(str_create("ffi-call: missing arguments"), pointer);
        }
        converted_args[i] = ffi_get_internal_data_from_type(obj_ffi->arg_types[i], get_car(args));
        args = get_cdr(args);
    }
    void* m = alloca(obj_ffi->ret_type->size);
    if (!m) {
        return err(str_create("ffi-call: alloca failed"), ffi);
    }
    ffi_call(&obj_ffi->cif, get_pointer(pointer), m, converted_args);
    obj_t* res = memory_from_data(m, ffi_type_to_obj_type(obj_ffi->ret_type));
    return res;

}

static obj_t* vlist_null_terminated(va_list args) {
    obj_t* obj = va_arg(args, obj_t*);
    if (!obj) {
        return memory_nil();
    }
    return memory_cons(obj, vlist_null_terminated(args));
}

static obj_t* apply_primitive(obj_t* op, obj_t* args, obj_t* env) {
    primitive_t primitive = get_primitive(op);
    obj_t* result = primitive(op, args, env);
    return result;
}

static obj_t* apply_compound(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* params = get_compound_params(op);
    obj_t* body = get_compound_body(op);
    obj_t* captured_env = get_compound_env(op);
    obj_t* evaled_args = list_of_values(args, env);
    obj_t* new_env = env_extend(captured_env, params, evaled_args);
    if (is_error(new_env)) {
        return new_env;
    }
    return begin(body, new_env);
}

static obj_t* apply_macro(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* params = get_macro_params(op);
    obj_t* body = get_macro_body(op);
    obj_t* new_env = env_extend(env, params, args);
    if (is_error(new_env)) {
        return new_env;
    }
    return begin(body, new_env);
}

static void* ffi_get_internal_data_from_type(ffi_type* type, obj_t* obj) {
    switch (type->type) {
    case FFI_TYPE_VOID: return NULL;
    case FFI_TYPE_SINT32: {
        assert(is_bool(obj));
        return &((obj_bool_t*)obj)->value;
    }
    case FFI_TYPE_POINTER: {
        assert(is_pointer(obj));
        return &((obj_pointer_t*)obj)->pointer;
    }
    case FFI_TYPE_DOUBLE: {
        assert(is_real(obj));
        return &((obj_real_t*)obj)->real;
    }
    default: assert(0 && "Unsupported FFI type");
    }
}

static void obj_lisp_type_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<lisp-type ");
    str_push(str, "%s", obj_type_to_string(get_lisp_type(obj)));
    str_push(str, ">");
}

static void obj_error_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<error ");
    str_push_str(str, get_error_message(obj));
    str_push(str, ">");
}

static void obj_eof_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<eof>");
}

static void obj_nil_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<nil>");
}

static void obj_void_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<void>");
}

static void obj_pointer_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<pointer ");
    str_push(str, "%p", get_pointer(obj));
    str_push(str, ">");
}

static void obj_bool_to_string(const obj_t* obj, str_t* str) {
    str_push(str, get_bool(obj) ? "#t" : "#f");
}

static void obj_cons_to_string(const obj_t* obj, str_t* str) {
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

static void obj_real_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "%f", get_real(obj));
}

static void obj_symbol_to_string(const obj_t* obj, str_t* str) {
    str_push_str(str, get_symbol(obj));
}

static void obj_string_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "\"");
    str_push_str(str, get_string(obj));
    str_push(str, "\"");
}

static void obj_file_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<file>");
}

static void obj_env_to_string(const obj_t* obj, str_t* str) {
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

static void obj_ffi_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<ffi>");
    // str_push_str(str, get_ffi_ret_type(obj));
    // str_push(str, " ");
    // obj_t* arg_types = get_ffi_arg_types(obj);
    // while (is_cons(arg_types)) {
    //     obj_to_string(get_car(arg_types), str);
    //     arg_types = get_cdr(arg_types);
    //     if (is_cons(arg_types)) {
    //         str_push(str, " ");
    //     }
    // }
    // str_push(str, ">");
}

static void obj_macro_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<macro ");
    obj_to_string(get_macro_params(obj), str);
    str_push(str, " ");
    obj_to_string(get_macro_body(obj), str);
    str_push(str, ">");
}

static void obj_primitive_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<primitive ");
    str_push_str(str, get_primitive_name(obj));
    str_push(str, ">");
}

static void obj_compound_to_string(const obj_t* obj, str_t* str) {
    str_push(str, "#<compound ");
    obj_to_string(get_compound_params(obj), str);
    str_push(str, " ");
    obj_to_string(get_compound_body(obj), str);
    str_push(str, " ");
    obj_to_string(get_compound_env(obj), str);
    str_push(str, ">");
}

static obj_t* eval(obj_t* obj, obj_t* env) {
    obj_t* expanded_obj = macroexpand(obj, env);
    if (is_error(expanded_obj)) {
        return expanded_obj;
    }

    obj_t* result = expanded_obj;

    if (is_symbol(expanded_obj)) {
        result = get_env_binding(env, expanded_obj);
        if (!result) {
            result = err(str_create("Eval: unbound variable"), obj, expanded_obj);
        }
    } else if (is_cons(expanded_obj)) {
        obj_t* op = eval(get_car(expanded_obj), env);
        obj_t* args = get_cdr(expanded_obj);
        result = apply(op, args, env);
    }

    return result;
}

static obj_t* apply(obj_t* op, obj_t* args, obj_t* env) {
    obj_t* result = 0;

    if (is_primitive(op)) {
        result = apply_primitive(op, args, env);
    } else if (is_compound(op)) {
        result = apply_compound(op, args, env);
    } else if (is_macro(op)) {
        result = apply_macro(op, args, env);
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

static obj_t* macroexpand_1(obj_t* op, obj_t* env) {
    obj_t* start = op;
    while (is_cons(op)) {
        obj_t* operator = get_car(op);
        obj_t* args = get_cdr(op);
        if (is_cons(operator)) {
            op = operator;
        } else {
            if (is_macro(operator)) {
                obj_t* expanded = apply_macro(operator, args, env);
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
                obj_t* binding = get_env_binding(env, operator);
                if (binding && is_macro(binding)) {
                    obj_t* expanded = apply_macro(binding, args, env);
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

static obj_t* macroexpand(obj_t* op, obj_t* env) {
    obj_t* result = op;
    if (is_cons(result)) {
        obj_t* operator = get_car(result);
        obj_t* args = get_cdr(result);
        obj_t* expanded_operator = macroexpand(operator, env);
        if (is_error(expanded_operator)) {
            return expanded_operator;
        }

        set_car(result, expanded_operator);
        if (is_macro(expanded_operator)) {
            result = apply_macro(expanded_operator, args, env);
        } else if (is_symbol(expanded_operator)) {
            obj_t* binding = get_env_binding(env, expanded_operator);
            if (binding && is_macro(binding)) {
                result = apply_macro(binding, args, env);
            }
        }
    }

    return result;
}

static void print(obj_t* obj, FILE* file) {
    if (!is_void(obj)) {
        str_t s = str();
        obj_to_string(obj, &s);
        fprintf(file, "%s\n", str_data(&s));
    }
}

static obj_t* list_null_terminated(universe_t* universe, ...) {
    va_list args;
    va_start(args, universe);
    obj_t* result = vlist_null_terminated(args);
    va_end(args);
    return result;
}

static bool is_list(obj_t* obj) {
    while (is_cons(obj)) {
        obj = get_cdr(obj);
    }
    return is_nil(obj);
}

static size_t list_length(obj_t* obj) {
    size_t length = 0;
    while (!is_nil(obj)) {
        ++length;
        obj = get_cdr(obj);
    }
    return length;
}

static obj_t* list_tail(obj_t* list, size_t index) {
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

static obj_t* list_ref(obj_t* list, size_t index) {
    return get_car(list_tail(list, index));
}

static bool is_eq(obj_t* obj1, obj_t* obj2) {
    return obj1 == obj2;
}

static bool is_true(obj_t* obj) {
    return !(is_false(obj));
}

static bool is_false(obj_t* obj) {
    return is_nil(obj) || (is_bool(obj) && !get_bool(obj));
}

static obj_t* begin(obj_t* obj, obj_t* env) {
    obj_t* result = memory_void();
    while (is_cons(obj)) {
        result = eval(get_car(obj), env);
        obj = get_cdr(obj);
    }
    return result;
}

static obj_t* list_of_values(obj_t* args, obj_t* env) {
    if (is_nil(args)) {
        return memory_nil();
    }
    return memory_cons(eval(get_car(args), env), list_of_values(get_cdr(args), env));
}

static obj_t* env_extend(obj_t* env, obj_t* params, obj_t* args) {
    obj_t* start_params = params;
    obj_t* start_args = args;
    assert(is_env(env));
    obj_t* dot = memory_symbol(str_create("."));
    obj_t* result = memory_env();
    set_env_parent(result, env);
    while (!is_nil(params) && !is_nil(args)) {
        if (is_eq(get_car(params), dot)) {
            params = get_cdr(params);
            define_env_binding(result, get_car(params), args);
            return result;
        }
        define_env_binding(result, get_car(params), get_car(args));
        params = get_cdr(params);
        args = get_cdr(args);
    }

    if (is_nil(params) && is_nil(args)) {
    } else if (is_nil(params) && !is_nil(args)) {
        result = err(str_create("Too many arguments"), start_params, start_args);
    } else if (!is_nil(params) && is_nil(args)) {
        if (is_eq(get_car(params), dot)) {
            define_env_binding(result, get_car(params), memory_nil());
        } else {
            result = err(str_create("Too few arguments"), start_params, start_args);
        }
    } else {
        assert(0);
    }

    return result;
}

static const char* to_string(obj_t* obj) {
    str_t s = str();
    obj_to_string(obj, &s);
    return str_data(&s);
}

static void obj_to_string(const obj_t* obj, str_t* str) {
    switch (obj->type) {
    case OBJ_TYPE_LISP_TYPE: {
        obj_lisp_type_to_string(obj, str);
    } break ;
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
    case OBJ_TYPE_POINTER: {
        obj_pointer_to_string(obj, str);
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
    case OBJ_TYPE_FFI: {
        obj_ffi_to_string(obj, str);
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

static obj_t* verr_null_terminated(const char* stringified_params, str_t message, va_list args) {
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
    return memory_error(formatted_message);
}

static obj_t* err_null_terminated(str_t message, const char* stringified_params, ...) {
    va_list args;
    va_start(args, stringified_params);
    obj_t* result = verr_null_terminated(stringified_params, message, args);
    va_end(args);
    return result;
}

static obj_t* get_env_binding(obj_t* obj, obj_t* key) {
    assert(is_env(obj));
    assert(is_symbol(key));
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        return interned_entry->obj;
    }
    obj_t* parent = get_env_parent(obj);
    if (parent) {
        return get_env_binding(parent, key);
    }
    return 0;
}

static obj_t* set_env_binding(obj_t* obj, obj_t* key, obj_t* value) {
    assert(is_env(obj));
    assert(is_symbol(key));
    assert(value);
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        interned_entry->obj = value;
        return value;
    }

    obj_t* parent = get_env_parent(obj);
    if (parent) {
        return set_env_binding(parent, key, value);
    }
    return err(str_create("set_env_binding: Binding not found"), obj, key, value);
}

static obj_t* define_env_binding(obj_t* obj, obj_t* key, obj_t* value) {
    assert(is_env(obj));
    assert(is_symbol(key));
    assert(value);
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        interned_entry->obj = value;
        return value;
    }

    interned_entry_t* interned_entry = interned_entries_insert(str_create_str(get_symbol(key)), value);
    hasher_insert(get_env_bindings(obj), interned_entry);
    return value;
}

static size_t interned_entries_key_hash(const void* key) {
    const str_t* s = (const str_t*)key;
    size_t hash = 5381;
    const size_t s_size = str_size(s);
    for (size_t i = 0; i < s_size; ++i) {
        hash = ((hash << 5) + hash) + str_at(s, i);
    }
    return hash;
}

static int interned_entries_key_compare(const void* key1, const void* key2) {
    const str_t* s1 = (const str_t*)key1;
    const str_t* s2 = (const str_t*)key2;
    return str_is_equal_str(s1, s2) ? 0 : 1;
}

static const void* interned_entries_entry_key(const void* entry) {
    return &((interned_entry_t*)entry)->s;
}

static interned_entry_t* interned_entries_insert(str_t s, obj_t* obj) {
    if (UNIVERSE.interned_entries_top == UNIVERSE.interned_entries_size) {
        size_t old_size = UNIVERSE.interned_entries_size;
        UNIVERSE.interned_entries_size *= 2;
        UNIVERSE.interned_entries = realloc(UNIVERSE.interned_entries, sizeof(*UNIVERSE.interned_entries) * UNIVERSE.interned_entries_size);
        for (size_t i = old_size; i < UNIVERSE.interned_entries_size; ++i) {
            UNIVERSE.interned_entries[i] = malloc(sizeof(interned_entry_t));
            UNIVERSE.interned_entries[i]->index = i;
        }
    }
    interned_entry_t* interned_entry = UNIVERSE.interned_entries[UNIVERSE.interned_entries_top];
    interned_entry->s = s;
    interned_entry->obj = obj;
    interned_entry->index = UNIVERSE.interned_entries_top;
    ++UNIVERSE.interned_entries_top;
    return interned_entry;
}

static void interned_entries_remove(size_t index) {
    assert(index < UNIVERSE.interned_entries_top);
    UNIVERSE.interned_entries[index] = UNIVERSE.interned_entries[UNIVERSE.interned_entries_top - 1];
    UNIVERSE.interned_entries[index]->index = index;
    str_destroy(&UNIVERSE.interned_entries[UNIVERSE.interned_entries_top - 1]->s);
    --UNIVERSE.interned_entries_top;

    const double load_factor = (double)UNIVERSE.interned_entries_top / (double)UNIVERSE.interned_entries_size;
    if (16 < UNIVERSE.interned_entries_size && load_factor < 0.25) {
        UNIVERSE.interned_entries_size /= 2;
        UNIVERSE.interned_entries = realloc(UNIVERSE.interned_entries, sizeof(*UNIVERSE.interned_entries) * UNIVERSE.interned_entries_size);
    }
}

static obj_t* memory_type(obj_type_t type) {
    switch (type) {
    case OBJ_TYPE_LISP_TYPE: return UNIVERSE.obj_lisp_type_type;
    case OBJ_TYPE_ERROR: return UNIVERSE.obj_error_type;
    case OBJ_TYPE_EOF: return UNIVERSE.obj_eof_type;
    case OBJ_TYPE_NIL: return UNIVERSE.obj_nil_type;
    case OBJ_TYPE_VOID: return UNIVERSE.obj_void_type;
    case OBJ_TYPE_POINTER: return UNIVERSE.obj_pointer_type;
    case OBJ_TYPE_BOOL: return UNIVERSE.obj_bool_type;
    case OBJ_TYPE_CONS: return UNIVERSE.obj_cons_type;
    case OBJ_TYPE_REAL: return UNIVERSE.obj_real_type;
    case OBJ_TYPE_SYMBOL: return UNIVERSE.obj_symbol_type;
    case OBJ_TYPE_STRING: return UNIVERSE.obj_string_type;
    case OBJ_TYPE_FILE: return UNIVERSE.obj_file_type;
    case OBJ_TYPE_ENV: return UNIVERSE.obj_env_type;
    case OBJ_TYPE_FFI: return UNIVERSE.obj_ffi_type;
    case OBJ_TYPE_MACRO: return UNIVERSE.obj_macro_type;
    case OBJ_TYPE_FUNCTION_PRIMITIVE: return UNIVERSE.obj_function_primitive_type;
    case OBJ_TYPE_FUNCTION_COMPOUND: return UNIVERSE.obj_function_compound_type;
    default: assert(0);
    }
}

static obj_t* memory_error(str_t message) {
    obj_error_t* obj_error = (obj_error_t*)malloc(sizeof(obj_error_t));
    UNIVERSE.total_allocated += sizeof(obj_error_t);
    obj_error_init(obj_error, message);
    return (obj_t*) obj_error;
}

static obj_t* memory_eof() {
    return UNIVERSE.obj_eof;
}

static obj_t* memory_nil() {
    return UNIVERSE.obj_nil;
}

static obj_t* memory_void() {
    return UNIVERSE.obj_void;
}

static obj_t* memory_pointer(void* pointer) {
    obj_pointer_t* obj_pointer = (obj_pointer_t*)malloc(sizeof(obj_pointer_t));
    UNIVERSE.total_allocated += sizeof(obj_pointer_t);
    obj_pointer_init(obj_pointer, pointer);
    return (obj_t*) obj_pointer;
}

static obj_t* memory_bool(bool boolean) {
    return boolean ? UNIVERSE.obj_true : UNIVERSE.obj_false;
}

static obj_t* memory_cons(obj_t* car, obj_t* cdr) {
    obj_cons_t* obj_cons = (obj_cons_t*)malloc(sizeof(obj_cons_t));
    UNIVERSE.total_allocated += sizeof(obj_cons_t);
    obj_cons_init(obj_cons, car, cdr);
    return (obj_t*) obj_cons;
}

static obj_t* memory_real(double real) {
    obj_real_t* obj_real = (obj_real_t*)malloc(sizeof(obj_real_t));
    UNIVERSE.total_allocated += sizeof(obj_real_t);
    obj_real_init(obj_real, real);
    return (obj_t*) obj_real;
}

static obj_t* memory_symbol(str_t symbol) {
    hasher_entry_t* entry = hasher_find(&UNIVERSE.interned_symbols, &symbol);
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        return interned_entry->obj;
    }
    obj_symbol_t* obj_symbol = (obj_symbol_t*)malloc(sizeof(obj_symbol_t));
    UNIVERSE.total_allocated += sizeof(obj_symbol_t);
    obj_symbol_init(obj_symbol, symbol);
    hasher_insert(&UNIVERSE.interned_symbols, interned_entries_insert(symbol, (obj_t*) obj_symbol));
    return (obj_t*) obj_symbol;
}

static obj_t* memory_string(str_t string) {
    obj_string_t* obj_string = (obj_string_t*)malloc(sizeof(obj_string_t));
    UNIVERSE.total_allocated += sizeof(obj_string_t);
    obj_string_init(obj_string, string);
    return (obj_t*) obj_string;
}

static obj_t* memory_file(FILE* file) {
    obj_file_t* obj_file = (obj_file_t*)malloc(sizeof(obj_file_t));
    UNIVERSE.total_allocated += sizeof(obj_file_t);
    obj_file_init(obj_file, file);
    return (obj_t*) obj_file;
}

static obj_t* memory_env() {
    obj_env_t* obj_env = (obj_env_t*)malloc(sizeof(obj_env_t));
    UNIVERSE.total_allocated += sizeof(obj_env_t);
    hasher_t bindings = hasher(
        interned_entries_key_hash,
        interned_entries_key_compare,
        interned_entries_entry_key
    );
    obj_env_init(obj_env, 0, bindings);
    return (obj_t*) obj_env;
}

static obj_t* memory_ffi() {
    obj_ffi_t* obj_ffi = (obj_ffi_t*)malloc(sizeof(obj_ffi_t));
    UNIVERSE.total_allocated += sizeof(obj_ffi_t);
    obj_ffi_create(obj_ffi);
    return (obj_t*) obj_ffi;
}

static obj_t* memory_macro(obj_t* params, obj_t* body) {
    obj_macro_t* obj_macro = (obj_macro_t*)malloc(sizeof(obj_macro_t));
    UNIVERSE.total_allocated += sizeof(obj_macro_t);
    obj_macro_init(obj_macro, params, body);
    return (obj_t*) obj_macro;
}

static obj_t* memory_primitive(str_t name, primitive_t primitive) {
    obj_primitive_t* obj_primitive = (obj_primitive_t*)malloc(sizeof(obj_primitive_t));
    UNIVERSE.total_allocated += sizeof(obj_primitive_t);
    obj_primitive_init(obj_primitive, name, primitive);
    return (obj_t*) obj_primitive;
}

static obj_t* memory_compound(obj_t* params, obj_t* body, obj_t* env) {
    obj_compound_t* obj_compound = (obj_compound_t*)malloc(sizeof(obj_compound_t));
    UNIVERSE.total_allocated += sizeof(obj_compound_t);
    obj_compound_init(obj_compound, params, body, env);
    return (obj_t*) obj_compound;
}

static obj_t* memory_from_data(void* data, obj_type_t type) {
    switch (type) {
    case OBJ_TYPE_VOID: return memory_void();
    case OBJ_TYPE_EOF: return memory_eof();
    case OBJ_TYPE_NIL: return memory_nil();
    case OBJ_TYPE_POINTER: return memory_pointer(*(void**)data);
    case OBJ_TYPE_BOOL: return memory_bool(*(bool*)data);
    case OBJ_TYPE_REAL: return memory_real(*(double*)data);
    default: assert(0);
    }
}

static obj_t* reader_skip_whitespaces(FILE* file) {
    while (!reader_is_at_end(file) && reader_is_whitespace(reader_peek(file))) {
        reader_getc(file);
    }
    return memory_void();
}

static obj_t* reader_double_quote(FILE* file) {
    str_t lexeme = str();
    while (!reader_is_at_end(file)) {
        char c = reader_getc(file);
        if (c == '"') {
            return memory_string(lexeme);
        }
        str_push(&lexeme, "%c", c);
    }
    str_t error_message = str_create("Unterminated string literal: ");
    str_push_str(&error_message, &lexeme);
    return memory_error(error_message);
}

static obj_t* reader_quote(FILE* file) {
    list(memory_symbol(str_create("quote")), reader_read(file));
}

static obj_t* reader_qauasiquote(FILE* file) {
    list(memory_symbol(str_create("quasiquote")), reader_read(file));
}

static obj_t* reader_comma(FILE* file) {
    if (reader_is_at_end(file)) {
        return memory_error(str_create("Unexpected end of file after comma"));
    }
    char c = reader_getc(file);
    switch (c) {
        case '@': {
            return list(memory_symbol(str_create("unquote-splicing")), reader_read(file));
        } break ;
        default: {
            reader_ungetc(file, c);
            return list(memory_symbol(str_create("unquote")), reader_read(file));
        }
    }
}

static obj_t* reader_right_parent(FILE* file) {
    return memory_symbol(str_create(")"));
}

static obj_t* reader_left_parent(FILE* file) {
    if (reader_is_at_end(file)) {
        return memory_error(str_create("Unexpected end of file after left parenthesis"));
    }

    obj_t* obj = reader_read(file);
    if (is_eq(obj, memory_symbol(str_create(")")))) {
        return memory_nil();
    }

    return memory_cons(obj, reader_left_parent(file));
}

static obj_t* reader_true(FILE* file) {
    return memory_bool(true);
}

static obj_t* reader_false(FILE* file) {
    return memory_bool(false);
}

static obj_t* reader_multiline_comment(FILE* file) {
    size_t depth = 1;
    return 0;
}

static void reader_node_init(reader_node_t* self) {
    memset(self, 0, sizeof(reader_node_t));
}

static void reader_node_destroy(reader_node_t* self) {
    for (int i = 0; i < sizeof(self->children) / sizeof(self->children[0]); i++) {
        if (self->children[i]) {
            reader_node_destroy(self->children[i]);
        }
    }
}

static void reader_register_reader_macro_str(const char* name, reader_function_t reader_function) {
    reader_node_t* node = &UNIVERSE.reader_node;
    while (*name) {
        const size_t child_index = (unsigned char)*name;
        assert(child_index < sizeof(node->children) / sizeof(node->children[0]));
        if (!node->children[child_index]) {
            node->children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
            reader_node_init(node->children[child_index]);
        }
        node = node->children[child_index];
        ++name;
    }
    node->reader_function = reader_function;
}

static void reader_register_reader_macro_char(char c, reader_function_t reader_function) {
    const size_t child_index = (unsigned char)c;
    assert(child_index < sizeof(UNIVERSE.reader_node.children) / sizeof(UNIVERSE.reader_node.children[0]));
    if (!UNIVERSE.reader_node.children[child_index]) {
        UNIVERSE.reader_node.children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
        reader_node_init(UNIVERSE.reader_node.children[child_index]);
    }
    UNIVERSE.reader_node.children[child_index]->reader_function = reader_function;
}

static char reader_peek(FILE* file) {
    char c = reader_getc(file);
    reader_ungetc(file, c);
    return c;
}

static char reader_getc(FILE* file) {
    char c = getc(file);
    if (c == EOF) {
        return '\0';
    }
    return c;
}

static void reader_ungetc(FILE* file, char c) {
    ungetc(c, file);
}

static bool reader_is_at_end(FILE* file) {
    char c = reader_getc(file);
    if (c == '\0') {
        return true;
    }
    reader_ungetc(file, c);
    return false;
}

static bool reader_is_whitespace(char c) {
    return isspace(c);
}

static obj_t* reader_default_function(FILE* file, str_t lexeme) {
    while (!reader_is_at_end(file)) {
        char c = reader_getc(file);
        size_t child_index = (unsigned char)c;
        if (sizeof(UNIVERSE.reader_node.children) / sizeof(UNIVERSE.reader_node.children[0]) <= child_index) {
            assert(0);
        }
        if (c == ')' || UNIVERSE.reader_node.children[child_index]) {
            reader_ungetc(file, c);
            break ;
        }
        str_push(&lexeme, "%c", c);
    }

    const size_t lexeme_size = str_size(&lexeme); 
    if (str_is_empty(&lexeme)) {
        return memory_void();
    } else if ((str_at(&lexeme, 0) == '.' && 1 < lexeme_size) || isdigit(str_at(&lexeme, 0))) {
        bool had_dot = false;
        for (size_t i = 0; i < lexeme_size; ++i) {
            char c = str_at(&lexeme, i);
            if (c == '.') {
                if (!had_dot) {
                    had_dot = true;
                } else {
                    return memory_symbol(lexeme);
                }
            } else if (isdigit(c)) {
            } else {
                return memory_symbol(lexeme);
            }
        }
        obj_t* result = memory_real(atof(str_data(&lexeme)));
        str_destroy(&lexeme);
        return result;
    } else {
        return memory_symbol(lexeme);
    }
}

static obj_t* reader_read(FILE* file) {
    if (reader_is_at_end(file)) {
        return memory_eof();
    }

    reader_node_t *node = &UNIVERSE.reader_node;
    str_t lexeme = str();
    reader_function_t reader_function = 0;
    while (node && !reader_is_at_end(file)) {
        char c = reader_getc(file);
        str_push(&lexeme, "%c", c);
        size_t child_index = (unsigned char)c;
        if (sizeof(node->children) / sizeof(node->children[0]) <= child_index) {
            assert(0);
        }
        node = node->children[child_index];
        if (node && node->reader_function) {
            reader_function = node->reader_function;
            str_clear(&lexeme);
        }
    }

    obj_t* result = 0;
    if (reader_function) {
        while (str_size(&lexeme)) {
            char c = str_pop(&lexeme);
            reader_ungetc(file, c);
        }
        result = reader_function(file);
    } else {
        result = reader_default_function(file, lexeme);
    }

    if (is_void(result)) {
        return reader_read(file);
    }

    return result;
}

bool universe_init() {
    memset(&UNIVERSE, 0, sizeof(universe_t));

    UNIVERSE.total_allocated = 0;

    UNIVERSE.obj_lisp_type_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_lisp_type_type, OBJ_TYPE_LISP_TYPE);

    UNIVERSE.obj_error_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_error_type, OBJ_TYPE_ERROR);

    UNIVERSE.obj_eof_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_eof_type, OBJ_TYPE_EOF);

    UNIVERSE.obj_nil_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_nil_type, OBJ_TYPE_NIL);

    UNIVERSE.obj_void_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_void_type, OBJ_TYPE_VOID);

    UNIVERSE.obj_pointer_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_pointer_type, OBJ_TYPE_POINTER);

    UNIVERSE.obj_bool_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_bool_type, OBJ_TYPE_BOOL);

    UNIVERSE.obj_cons_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_cons_type, OBJ_TYPE_CONS);

    UNIVERSE.obj_real_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_real_type, OBJ_TYPE_REAL);

    UNIVERSE.obj_symbol_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_symbol_type, OBJ_TYPE_SYMBOL);

    UNIVERSE.obj_string_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_string_type, OBJ_TYPE_STRING);

    UNIVERSE.obj_file_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_file_type, OBJ_TYPE_FILE);

    UNIVERSE.obj_env_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_env_type, OBJ_TYPE_ENV);

    UNIVERSE.obj_ffi_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_ffi_type, OBJ_TYPE_FFI);

    UNIVERSE.obj_macro_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_macro_type, OBJ_TYPE_MACRO);

    UNIVERSE.obj_function_primitive_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_function_primitive_type, OBJ_TYPE_FUNCTION_PRIMITIVE);

    UNIVERSE.obj_function_compound_type = malloc(sizeof(obj_lisp_type_t));
    UNIVERSE.total_allocated += sizeof(obj_lisp_type_t);
    obj_lisp_type_init((obj_lisp_type_t*)UNIVERSE.obj_function_compound_type, OBJ_TYPE_FUNCTION_COMPOUND);

    UNIVERSE.obj_eof = malloc(sizeof(obj_eof_t));
    UNIVERSE.total_allocated += sizeof(obj_eof_t);
    obj_eof_init((obj_eof_t*)UNIVERSE.obj_eof);

    UNIVERSE.obj_nil = malloc(sizeof(obj_nil_t));
    UNIVERSE.total_allocated += sizeof(obj_nil_t);
    obj_nil_init((obj_nil_t*)UNIVERSE.obj_nil);

    UNIVERSE.obj_void = malloc(sizeof(obj_void_t));
    UNIVERSE.total_allocated += sizeof(obj_void_t);
    obj_void_init((obj_void_t*)UNIVERSE.obj_void);

    UNIVERSE.obj_true = malloc(sizeof(obj_bool_t));
    UNIVERSE.total_allocated += sizeof(obj_bool_t);
    obj_bool_init((obj_bool_t*)UNIVERSE.obj_true, true);

    UNIVERSE.obj_false = malloc(sizeof(obj_bool_t));
    UNIVERSE.total_allocated += sizeof(obj_bool_t);
    obj_bool_init((obj_bool_t*)UNIVERSE.obj_false, false);

    reader_node_init(&UNIVERSE.reader_node);
    for (size_t i = 0; i < sizeof(UNIVERSE.reader_node.children) / sizeof(UNIVERSE.reader_node.children[0]); i++) {
        if (reader_is_whitespace((char)i)) {
            reader_register_reader_macro_char((char)i, &reader_skip_whitespaces);
        }
    }
    reader_register_reader_macro_str("\"", &reader_double_quote);
    reader_register_reader_macro_str("'", &reader_quote);
    reader_register_reader_macro_str("`", &reader_qauasiquote);
    reader_register_reader_macro_str(",", &reader_comma);
    reader_register_reader_macro_str(")", &reader_right_parent);
    reader_register_reader_macro_str("(", &reader_left_parent);
    reader_register_reader_macro_str("#t", &reader_true);
    reader_register_reader_macro_str("#f", &reader_false);

    UNIVERSE.env = memory_env();

    UNIVERSE.interned_entries_size = 16;
    UNIVERSE.interned_entries_top = 0;
    UNIVERSE.interned_entries = malloc(sizeof(*UNIVERSE.interned_entries) * UNIVERSE.interned_entries_size);
    for (size_t i = 0; i < UNIVERSE.interned_entries_size; ++i) {
        UNIVERSE.interned_entries[i] = malloc(sizeof(interned_entry_t));
        UNIVERSE.interned_entries[i]->index = i;
    }
    UNIVERSE.interned_symbols = hasher(
        interned_entries_key_hash,
        interned_entries_key_compare,
        interned_entries_entry_key
    );

    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-lisp-type")), UNIVERSE.obj_lisp_type_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-error")), UNIVERSE.obj_error_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-eof")), UNIVERSE.obj_eof_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-nil")), UNIVERSE.obj_nil_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-void")), UNIVERSE.obj_void_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-pointer")), UNIVERSE.obj_pointer_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-bool")), UNIVERSE.obj_bool_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-cons")), UNIVERSE.obj_cons_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-real")), UNIVERSE.obj_real_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-symbol")), UNIVERSE.obj_symbol_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-string")), UNIVERSE.obj_string_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-file")), UNIVERSE.obj_file_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-env")), UNIVERSE.obj_env_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-ffi")), UNIVERSE.obj_ffi_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-macro")), UNIVERSE.obj_macro_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-function-primitive")), UNIVERSE.obj_function_primitive_type);
    define_env_binding(UNIVERSE.env, memory_symbol(str_create("type-function-compound")), UNIVERSE.obj_function_compound_type);

#define _REGISTER_PRIMITIVE(name, fn) define_env_binding(UNIVERSE.env, memory_symbol(str_create(name)), memory_primitive(str_create(name), fn))
    _REGISTER_PRIMITIVE("define", &primitive_define);
    _REGISTER_PRIMITIVE("set!", &primitive_set);
    _REGISTER_PRIMITIVE("quote", &primitive_quote);
    _REGISTER_PRIMITIVE("macroexpand", &primitive_macroexpand);
    _REGISTER_PRIMITIVE("macroexpand-1", &primitive_macroexpand_1);
    _REGISTER_PRIMITIVE("macro", &primitive_macro);
    _REGISTER_PRIMITIVE("lambda", &primitive_lambda);
    _REGISTER_PRIMITIVE("if", &primitive_if);
    _REGISTER_PRIMITIVE("car", &primitive_car);
    _REGISTER_PRIMITIVE("cdr", &primitive_cdr);
    _REGISTER_PRIMITIVE("eq?", &primitive_eq);
    _REGISTER_PRIMITIVE("read", &primitive_read);
    _REGISTER_PRIMITIVE("write", &primitive_write);
    _REGISTER_PRIMITIVE("eval", &primitive_eval);
    _REGISTER_PRIMITIVE("apply", &primitive_apply);
    _REGISTER_PRIMITIVE("open", &primitive_fopen);
    _REGISTER_PRIMITIVE("ffi", &primitive_ffi);
    _REGISTER_PRIMITIVE("dlsym", &primitive_dlsym);
    _REGISTER_PRIMITIVE("ffi-call", &primitive_ffi_call);

#undef _REGISTER_PRIMITIVE

    UNIVERSE.dlhandle = dlopen(0, RTLD_LAZY);
    // UNIVERSE.dlhandle = dlopen(0, RTLD_GLOBAL | RTLD_NOW);
    if (!UNIVERSE.dlhandle) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        return false;
    }

    return true;
}

void universe_destroy() {
    reader_node_destroy(&UNIVERSE.reader_node);
    free(UNIVERSE.obj_eof);
    free(UNIVERSE.obj_nil);
    free(UNIVERSE.obj_void);
    free(UNIVERSE.obj_true);
    free(UNIVERSE.obj_false);
    for (size_t i = 0; i < UNIVERSE.interned_entries_top; ++i) {
        str_destroy(&UNIVERSE.interned_entries[i]->s);
    }
    hasher_destroy(&UNIVERSE.interned_symbols);
    dlclose(UNIVERSE.dlhandle);
}

void universe_run() {
    while (1) {
        printf("> ");
        obj_t* read_obj = reader_read(stdin);
        if (is_eof(read_obj)) {
            break ;
        }

        obj_t* evaled_obj = eval(read_obj, UNIVERSE.env);

        print(evaled_obj, stdout);
    }
}
