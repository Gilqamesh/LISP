#include "obj.h"

void obj_init(obj_t* obj, obj_type_t obj_type) {
    obj->type = obj_type;
}

obj_type_t type(const obj_t* obj) {
    return obj->type;
}

void obj_error_init(obj_error_t* obj_error, str_t message) {
    obj_init(&obj_error->base, OBJ_TYPE_ERROR);
    obj_error->message = message;
}

bool is_error(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_ERROR;
}

const str_t* get_error_message(const obj_t* obj) {
    assert(is_error(obj));
    return &((obj_error_t*)obj)->message;
}

void obj_eof_init(obj_eof_t* obj_eof) {
    obj_init(&obj_eof->base, OBJ_TYPE_EOF);
}

bool is_eof(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_EOF;
}

void obj_nil_init(obj_nil_t* obj_nil) {
    obj_init(&obj_nil->base, OBJ_TYPE_NIL);
}

bool is_nil(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_NIL;
}

void obj_void_init(obj_void_t* obj_void) {
    obj_init(&obj_void->base, OBJ_TYPE_VOID);
}

bool is_void(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_VOID;
}

void obj_bool_init(obj_bool_t* obj_bool, bool value) {
    obj_init(&obj_bool->base, OBJ_TYPE_BOOL);
    obj_bool->value = value;
}

bool is_bool(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_BOOL;
}

bool get_bool(const obj_t* obj) {
    assert(is_bool(obj));
    return ((obj_bool_t*)obj)->value;
}

void obj_cons_init(obj_cons_t* obj_cons, obj_t* car, obj_t* cdr) {
    obj_init(&obj_cons->base, OBJ_TYPE_CONS);
    obj_cons->car = car;
    obj_cons->cdr = cdr;
}

bool is_cons(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_CONS;
}

obj_t* get_car(const obj_t* obj) {
    assert(is_cons(obj));
    return ((obj_cons_t*)obj)->car;
}

obj_t* get_cdr(const obj_t* obj) {
    assert(is_cons(obj));
    return ((obj_cons_t*)obj)->cdr;
}

void set_car(obj_t* obj, obj_t* car) {
    assert(is_cons(obj));
    ((obj_cons_t*)obj)->car = car;
}

void set_cdr(obj_t* obj, obj_t* cdr) {
    assert(is_cons(obj));
    ((obj_cons_t*)obj)->cdr = cdr;
}

void obj_real_init(obj_real_t* obj_real, double real) {
    obj_init(&obj_real->base, OBJ_TYPE_REAL);
    obj_real->real = real;
}

bool is_real(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_REAL;
}

double get_real(const obj_t* obj) {
    assert(is_real(obj));
    return ((obj_real_t*)obj)->real;
}

void obj_symbol_init(obj_symbol_t* obj_symbol, str_t symbol) {
    obj_init(&obj_symbol->base, OBJ_TYPE_SYMBOL);
    obj_symbol->symbol = symbol;
}

bool is_symbol(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_SYMBOL;
}

const str_t* get_symbol(const obj_t* obj) {
    assert(is_symbol(obj));
    return &((obj_symbol_t*)obj)->symbol;
}

void obj_string_init(obj_string_t* obj_string, str_t string) {
    obj_init(&obj_string->base, OBJ_TYPE_STRING);
    obj_string->string = string;
}

bool is_string(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_STRING;
}

const str_t* get_string(const obj_t* obj) {
    assert(is_string(obj));
    return &((obj_string_t*)obj)->string;
}

void obj_file_init(obj_file_t* obj_file, FILE* file) {
    obj_init(&obj_file->base, OBJ_TYPE_FILE);
    obj_file->file = file;
}

bool is_file(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_FILE;
}

FILE* get_file(const obj_t* obj) {
    assert(is_file(obj));
    return ((obj_file_t*)obj)->file;
}

void obj_env_init(obj_env_t* obj_env, obj_t* parent, hasher_t bindings) {
    obj_init(&obj_env->base, OBJ_TYPE_ENV);
    obj_env->parent = parent;
    obj_env->bindings = bindings;
}

bool is_env(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_ENV;
}

obj_t* get_env_parent(const obj_t* obj) {
    assert(is_env(obj));
    return ((obj_env_t*)obj)->parent;
}

void set_env_parent(obj_t* obj, obj_t* parent) {
    assert(is_env(obj));
    ((obj_env_t*)obj)->parent = parent;
}

hasher_t* get_env_bindings(const obj_t* obj) {
    assert(is_env(obj));
    return &((obj_env_t*)obj)->bindings;
}

void obj_macro_init(obj_macro_t* obj_macro, obj_t* params, obj_t* body) {
    obj_init(&obj_macro->base, OBJ_TYPE_MACRO);
    obj_macro->params = params;
    obj_macro->body = body;
}

bool is_macro(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_MACRO;
}

obj_t* get_macro_params(const obj_t* obj) {
    assert(is_macro(obj));
    return ((obj_macro_t*)obj)->params;
}

obj_t* get_macro_body(const obj_t* obj) {
    assert(is_macro(obj));
    return ((obj_macro_t*)obj)->body;
}

void obj_primitive_init(obj_primitive_t* obj_primitive, str_t name, primitive_t primitive) {
    obj_init(&obj_primitive->base, OBJ_TYPE_FUNCTION_PRIMITIVE);
    obj_primitive->primitive = primitive;
    obj_primitive->name = name;
}

bool is_primitive(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_FUNCTION_PRIMITIVE;
}

primitive_t get_primitive(const obj_t* obj) {
    assert(is_primitive(obj));
    return ((obj_primitive_t*)obj)->primitive;
}

const str_t* get_primitive_name(const obj_t* obj) {
    assert(is_primitive(obj));
    return &((obj_primitive_t*)obj)->name;
}

void obj_compound_init(obj_compound_t* obj_compound, obj_t* params, obj_t* body, obj_t* env) {
    obj_init(&obj_compound->base, OBJ_TYPE_FUNCTION_COMPOUND);
    obj_compound->params = params;
    obj_compound->body = body;
    obj_compound->env = env;
}

bool is_compound(const obj_t* obj) {
    return type(obj) == OBJ_TYPE_FUNCTION_COMPOUND;
}

obj_t* get_compound_params(const obj_t* obj) {
    assert(is_compound(obj));
    return ((obj_compound_t*)obj)->params;
}

obj_t* get_compound_body(const obj_t* obj) {
    assert(is_compound(obj));
    return ((obj_compound_t*)obj)->body;
}

obj_t* get_compound_env(const obj_t* obj) {
    assert(is_compound(obj));
    return ((obj_compound_t*)obj)->env;
}
