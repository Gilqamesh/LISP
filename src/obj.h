#ifndef OBJ_H
# define OBJ_H

# include "libc.h"
# include "err.h"
# include "utils.h"

typedef struct obj_lisp_type_t obj_lisp_type_t;
typedef struct obj_cons_t obj_cons_t;
typedef struct obj_error_t obj_error_t;
typedef struct obj_eof_t obj_eof_t;
typedef struct obj_nil_t obj_nil_t;
typedef struct obj_pointer_t obj_pointer_t;
typedef struct obj_bool_t obj_bool_t;
typedef struct obj_void_t obj_void_t;
typedef struct obj_i8_t obj_i8_t;
typedef struct obj_u8_t obj_u8_t;
typedef struct obj_i16_t obj_i16_t;
typedef struct obj_u16_t obj_u16_t;
typedef struct obj_i32_t obj_i32_t;
typedef struct obj_u32_t obj_u32_t;
typedef struct obj_i64_t obj_i64_t;
typedef struct obj_u64_t obj_u64_t;
typedef struct obj_r32_t obj_r32_t;
typedef struct obj_r64_t obj_r64_t;
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
typedef struct obj_reader_t obj_reader_t;

typedef enum obj_type_t {
    OBJ_TYPE_LISP_TYPE,
    OBJ_TYPE_CONS,
    OBJ_TYPE_ERROR,
    OBJ_TYPE_EOF,
    OBJ_TYPE_NIL,
    OBJ_TYPE_POINTER,
    OBJ_TYPE_BOOL,
    OBJ_TYPE_VOID,
    OBJ_TYPE_I8,
    OBJ_TYPE_U8,
    OBJ_TYPE_I16,
    OBJ_TYPE_U16,
    OBJ_TYPE_I32,
    OBJ_TYPE_U32,
    OBJ_TYPE_I64,
    OBJ_TYPE_U64,
    OBJ_TYPE_R32,
    OBJ_TYPE_R64,
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
    OBJ_TYPE_READER,
    _OBJ_TYPE_SIZE
} obj_type_t;

const char* obj_type_to_string(obj_type_t type);

typedef struct obj_t {
    obj_type_t type;
} obj_t;

void obj_init(obj_t* self, obj_type_t type);
void obj_delete(obj_t* self);
obj_type_t obj_get_type(const obj_t* self);

void obj_to_string(const obj_t* self, obj_string_t* other);
obj_ffi_t* obj_to_ffi(const obj_t* self);
obj_t* obj_copy(const obj_t* self);
bool obj_equal(const obj_t* self, const obj_t* other);
bool obj_is_truthy(const obj_t* self);
bool obj_is_eq(const obj_t* self, const obj_t* other);
size_t obj_hash(const obj_t* self);
obj_t* obj_eval(const obj_t* self, obj_env_t* env);
obj_t* obj_apply(const obj_t* self, obj_t* args, obj_env_t* env);

#endif // OBJ_H
