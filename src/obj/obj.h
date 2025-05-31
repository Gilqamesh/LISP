#ifndef OBJ_H
# define OBJ_H

# include "libc.h"

# include "err.h"
typedef struct obj_lisp_type_t obj_lisp_type_t;
typedef struct obj_combination_t obj_combination_t;
typedef struct obj_error_t obj_error_t;
typedef struct obj_eof_t obj_eof_t;
typedef struct obj_nil_t obj_nil_t;
typedef struct obj_pointer_t obj_pointer_t;
typedef struct obj_bool_t obj_bool_t;
typedef struct obj_void_t obj_void_t;
typedef struct obj_char_t obj_char_t;
typedef struct obj_uchar_t obj_uchar_t;
typedef struct obj_int_t obj_int_t;
typedef struct obj_uint_t obj_uint_t;
typedef struct obj_short_t obj_short_t;
typedef struct obj_ushort_t obj_ushort_t;
typedef struct obj_long_t obj_long_t;
typedef struct obj_ulong_t obj_ulong_t;
typedef struct obj_size_t_t obj_size_t_t;
typedef struct obj_float_t obj_float_t;
typedef struct obj_double_t obj_double_t;
typedef struct obj_symbol_t obj_symbol_t;
typedef struct obj_string_t obj_string_t;
typedef struct obj_file_t obj_file_t;
typedef struct obj_env_t obj_env_t;
typedef struct obj_array_t obj_array_t;
typedef struct obj_hash_table_t obj_hash_table_t;
typedef struct obj_ffi_t obj_ffi_t;
typedef struct obj_macro_t obj_macro_t;
typedef struct obj_closure_t obj_closure_t;
typedef struct obj_primitive_t obj_primitive_t;
typedef struct obj_repl_t obj_repl_t;

typedef enum obj_type_t {
    OBJ_TYPE_LISP_TYPE,
    OBJ_TYPE_COMBINATION,
    OBJ_TYPE_ERROR,
    OBJ_TYPE_EOF,
    OBJ_TYPE_NIL,
    OBJ_TYPE_POINTER,
    OBJ_TYPE_BOOL,
    OBJ_TYPE_VOID,
    OBJ_TYPE_CHAR,
    OBJ_TYPE_UCHAR,
    OBJ_TYPE_INT,
    OBJ_TYPE_UINT,
    OBJ_TYPE_SHORT,
    OBJ_TYPE_USHORT,
    OBJ_TYPE_LONG,
    OBJ_TYPE_ULONG,
    OBJ_TYPE_SIZE_T,
    OBJ_TYPE_FLOAT,
    OBJ_TYPE_DOUBLE,
    OBJ_TYPE_SYMBOL,
    OBJ_TYPE_STRING,
    OBJ_TYPE_FILE,
    OBJ_TYPE_ENV,
    OBJ_TYPE_ARRAY,
    OBJ_TYPE_HASH_TABLE,
    OBJ_TYPE_FFI,
    OBJ_TYPE_MACRO,
    OBJ_TYPE_CLOSURE,
    OBJ_TYPE_PRIMITIVE,
    OBJ_TYPE_REPL,
    _OBJ_TYPE_SIZE
} obj_type_t;

const char* obj_type_to_string(obj_type_t type);

typedef struct obj_t {
    obj_type_t type;
} obj_t;

void obj_init(obj_t* self, obj_type_t type);
obj_type_t obj_get_type(const obj_t* self);

void obj_to_string(const obj_t* self, obj_string_t* other);
obj_ffi_t* obj_to_ffi(const obj_t* self);
obj_t* obj_copy(const obj_t* self);
bool obj_equal(const obj_t* self, const obj_t* other);
size_t obj_hash(const obj_t* self);
obj_t* obj_eval(const obj_t* self, obj_env_t* env);
obj_t* obj_apply(const obj_t* self, obj_array_t* args, obj_env_t* env);

#endif // OBJ_H
