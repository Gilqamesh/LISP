#ifndef OBJ_H
# define OBJ_H

# include "str.h"
# include "hasher.h"

# include <ffi.h>

typedef enum obj_type_t {
    OBJ_TYPE_LISP_TYPE,
    OBJ_TYPE_ERROR,
    OBJ_TYPE_EOF,
    OBJ_TYPE_NIL,
    OBJ_TYPE_VOID,
    OBJ_TYPE_POINTER,
    OBJ_TYPE_BOOL,
    OBJ_TYPE_INT32,
    OBJ_TYPE_INT64,
    OBJ_TYPE_CONS,
    OBJ_TYPE_REAL,
    OBJ_TYPE_SYMBOL,
    OBJ_TYPE_STRING,
    OBJ_TYPE_FILE,
    OBJ_TYPE_ENV,
    OBJ_TYPE_FFI,

    OBJ_TYPE_MACRO,

    OBJ_TYPE_FUNCTION_PRIMITIVE,
    OBJ_TYPE_FUNCTION_COMPOUND,

    _OBJ_TYPE_SIZE
} obj_type_t;
const char* obj_type_to_string(obj_type_t type);

typedef struct obj_t {
    obj_type_t type;
} obj_t;
void obj_init(obj_t* obj, obj_type_t obj_type);
obj_type_t type(const obj_t* obj);

typedef struct obj_lisp_type_t {
    obj_t base;
    obj_type_t type;
} obj_lisp_type_t;
void obj_lisp_type_init(obj_lisp_type_t* obj_lisp_type, obj_type_t type);
bool is_lisp_type(const obj_t* obj);
obj_type_t get_lisp_type(const obj_t* obj);

typedef struct obj_error_t {
    obj_t base;
    str_t message;
} obj_error_t;
void obj_error_init(obj_error_t* obj_error, str_t message);
bool is_error(const obj_t* obj);
const str_t* get_error_message(const obj_t* obj);

typedef struct obj_eof_t {
    obj_t base;
} obj_eof_t;
void obj_eof_init(obj_eof_t* obj_eof);
bool is_eof(const obj_t* obj);

typedef struct obj_nil_t {
    obj_t base;
} obj_nil_t;
void obj_nil_init(obj_nil_t* obj_nil);
bool is_nil(const obj_t* obj);

typedef struct obj_void_t {
    obj_t base;
} obj_void_t;
void obj_void_init(obj_void_t* obj_void);
bool is_void(const obj_t* obj);

typedef struct obj_pointer_t {
    obj_t base;
    void* pointer;
} obj_pointer_t;
void obj_pointer_init(obj_pointer_t* obj_pointer, void* pointer);
bool is_pointer(const obj_t* obj);
void* get_pointer(const obj_t* obj);

typedef struct obj_bool_t {
    obj_t base;
    bool value;
} obj_bool_t;
void obj_bool_init(obj_bool_t* obj_bool, bool value);
bool is_bool(const obj_t* obj);
bool get_bool(const obj_t* obj);

typedef struct obj_int32_t {
    obj_t base;
    int32_t value;
} obj_int32_t;
void obj_int32_init(obj_int32_t* obj_int32, int32_t value);
bool is_int32(const obj_t* obj);
int32_t get_int32(const obj_t* obj);

typedef struct obj_int64_t {
    obj_t base;
    int64_t value;
} obj_int64_t;
void obj_int64_init(obj_int64_t* obj_int64, int64_t value);
bool is_int64(const obj_t* obj);
int64_t get_int64(const obj_t* obj);

typedef struct obj_cons_t {
    obj_t base;
    obj_t* car;
    obj_t* cdr;
} obj_cons_t;
void obj_cons_init(obj_cons_t* obj_cons, obj_t* car, obj_t* cdr);
bool is_cons(const obj_t* obj);
obj_t* get_car(const obj_t* obj);
obj_t* get_cdr(const obj_t* obj);
void set_car(obj_t* obj, obj_t* car);
void set_cdr(obj_t* obj, obj_t* cdr);

typedef struct obj_real_t {
    obj_t base;
    double real;
} obj_real_t;
void obj_real_init(obj_real_t* obj_real, double real);
bool is_real(const obj_t* obj);
double get_real(const obj_t* obj);

typedef struct obj_symbol_t {
    obj_t base;
    str_t symbol;
} obj_symbol_t;
void obj_symbol_init(obj_symbol_t* obj_symbol, str_t symbol);
bool is_symbol(const obj_t* obj);
const str_t* get_symbol(const obj_t* obj);

typedef struct obj_string_t {
    obj_t base;
    str_t string;
} obj_string_t;
void obj_string_init(obj_string_t* obj_string, str_t string);
bool is_string(const obj_t* obj);
const str_t* get_string(const obj_t* obj);

typedef struct obj_file_t {
    obj_t base;
    FILE* file;
} obj_file_t;
void obj_file_init(obj_file_t* obj_fd, FILE* file);

bool is_file(const obj_t* obj);
FILE* get_file(const obj_t* obj);

typedef struct obj_env_t {
    obj_t base;
    obj_t* parent;
    hasher_t bindings; // obj_symbol_t to obj_t
} obj_env_t;
void obj_env_init(obj_env_t* obj_env, obj_t* parent, hasher_t bindings);
bool is_env(const obj_t* obj);
obj_t* get_env_parent(const obj_t* obj);
void set_env_parent(obj_t* obj, obj_t* parent);
hasher_t* get_env_bindings(const obj_t* obj);

typedef struct obj_ffi_t {
    obj_t base;
    ffi_cif cif;
    size_t arg_types_top;
    size_t arg_types_size;
    ffi_type** ffi_arg_types;
    ffi_type* ret_type_ffi;
    obj_t** arg_types;
    obj_t* ret_type;
} obj_ffi_t;
void obj_ffi_create(obj_ffi_t* obj_ffi);
void obj_ffi_destroy(obj_ffi_t* obj_ffi);
bool is_ffi(const obj_t* obj);
void set_ffi_ret_type(obj_t* obj, obj_t* type);
obj_t* get_ffi_ret_type(const obj_t* obj);
void add_ffi_arg_type(obj_t* obj, obj_t* type);
obj_t* get_ffi_arg_type(const obj_t* obj, size_t index);
size_t get_ffi_nargs(const obj_t* obj);
bool obj_ffi_finalize(obj_t* obj_ffi);
ffi_type* obj_type_to_ffi_type(const obj_t* obj);
size_t get_ffi_type_size(const obj_t* obj);

typedef struct obj_macro_t {
    obj_t base;
    obj_t* params;
    obj_t* body;
} obj_macro_t;
void obj_macro_init(obj_macro_t* obj_macro, obj_t* params, obj_t* body);
bool is_macro(const obj_t* obj);
obj_t* get_macro_params(const obj_t* obj);
obj_t* get_macro_body(const obj_t* obj);

typedef obj_t* (*primitive_t)(obj_t* op, obj_t* args, obj_t* env);
typedef struct obj_primitive_t {
    obj_t base;
    primitive_t primitive;
    str_t name;
} obj_primitive_t;
void obj_primitive_init(obj_primitive_t* obj_primitive, str_t name, primitive_t primitive);
bool is_primitive(const obj_t* obj);
primitive_t get_primitive(const obj_t* obj);
const str_t* get_primitive_name(const obj_t* obj);

typedef struct obj_compound_t {
    obj_t base;
    obj_t* params;
    obj_t* body;
    obj_t* env;
} obj_compound_t;
void obj_compound_init(obj_compound_t* obj_compound, obj_t* params, obj_t* body, obj_t* env);
bool is_compound(const obj_t* obj);
obj_t* get_compound_params(const obj_t* obj);
obj_t* get_compound_body(const obj_t* obj);
obj_t* get_compound_env(const obj_t* obj);

#endif // OBJ_H
