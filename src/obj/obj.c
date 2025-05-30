#include "obj.h"

#include "obj_lisp_type.h"
#include "obj_error.h"
#include "obj_eof.h"
#include "obj_nil.h"
#include "obj_pointer.h"
#include "obj_bool.h"
#include "obj_void.h"
#include "obj_char.h"
#include "obj_uchar.h"
#include "obj_int.h"
#include "obj_uint.h"
#include "obj_short.h"
#include "obj_ushort.h"
#include "obj_long.h"
#include "obj_ulong.h"
#include "obj_size_t.h"
#include "obj_float.h"
#include "obj_double.h"
#include "obj_symbol.h"
#include "obj_string.h"
#include "obj_file.h"
#include "obj_env.h"
#include "obj_array.h"
#include "obj_hash_table.h"
#include "obj_ffi.h"
#include "obj_macro.h"
#include "obj_closure.h"
#include "obj_primitive.h"
#include "obj_repl.h"

const char* obj_type_to_string(obj_type_t type) {
    switch (type) {
        case OBJ_TYPE_LISP_TYPE: return "lisp_type";
        case OBJ_TYPE_ERROR: return "error";
        case OBJ_TYPE_EOF: return "eof";
        case OBJ_TYPE_NIL: return "nil";
        case OBJ_TYPE_POINTER: return "pointer";
        case OBJ_TYPE_BOOL: return "bool";
        case OBJ_TYPE_VOID: return "void";
        case OBJ_TYPE_CHAR: return "char";
        case OBJ_TYPE_UCHAR: return "uchar";
        case OBJ_TYPE_INT: return "int";
        case OBJ_TYPE_UINT: return "uint";
        case OBJ_TYPE_SHORT: return "short";
        case OBJ_TYPE_USHORT: return "ushort";
        case OBJ_TYPE_LONG: return "long";
        case OBJ_TYPE_ULONG: return "ulong";
        case OBJ_TYPE_SIZE_T: return "size_t";
        case OBJ_TYPE_FLOAT: return "float";
        case OBJ_TYPE_DOUBLE: return "double";
        case OBJ_TYPE_SYMBOL: return "symbol";
        case OBJ_TYPE_STRING: return "string";
        case OBJ_TYPE_FILE: return "file";
        case OBJ_TYPE_ENV: return "env";
        case OBJ_TYPE_ARRAY: return "array";
        case OBJ_TYPE_HASH_TABLE: return "hash_table";
        case OBJ_TYPE_FFI: return "ffi";
        case OBJ_TYPE_MACRO: return "macro";
        case OBJ_TYPE_CLOSURE: return "closure";
        case OBJ_TYPE_PRIMITIVE: return "primitive";
        case OBJ_TYPE_REPL: return "repl";
        default: assert(0);
    }
}

void obj_init(obj_t* self, obj_type_t type) {
    self->type = type;
}

obj_type_t obj_get_type(const obj_t* self) {
    return self->type;
}

void obj_to_string(const obj_t* self, obj_string_t* other) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: obj_lisp_type_to_string((obj_lisp_type_t*)self, other); break;
        case OBJ_TYPE_ERROR: obj_error_to_string((obj_error_t*)self, other); break;
        case OBJ_TYPE_EOF: obj_eof_to_string((obj_eof_t*)self, other); break;
        case OBJ_TYPE_NIL: obj_nil_to_string((obj_nil_t*)self, other); break;
        case OBJ_TYPE_POINTER: obj_pointer_to_string((obj_pointer_t*)self, other); break;
        case OBJ_TYPE_BOOL: obj_bool_to_string((obj_bool_t*)self, other); break;
        case OBJ_TYPE_VOID: obj_void_to_string((obj_void_t*)self, other); break;
        case OBJ_TYPE_CHAR: obj_char_to_string((obj_char_t*)self, other); break;
        case OBJ_TYPE_UCHAR: obj_uchar_to_string((obj_uchar_t*)self, other); break;
        case OBJ_TYPE_INT: obj_int_to_string((obj_int_t*)self, other); break;
        case OBJ_TYPE_UINT: obj_uint_to_string((obj_uint_t*)self, other); break;
        case OBJ_TYPE_SHORT: obj_short_to_string((obj_short_t*)self, other); break;
        case OBJ_TYPE_USHORT: obj_ushort_to_string((obj_ushort_t*)self, other); break;
        case OBJ_TYPE_LONG: obj_long_to_string((obj_long_t*)self, other); break;
        case OBJ_TYPE_ULONG: obj_ulong_to_string((obj_ulong_t*)self, other); break;
        case OBJ_TYPE_SIZE_T: obj_size_t_to_string((obj_size_t_t*)self, other); break;
        case OBJ_TYPE_FLOAT: obj_float_to_string((obj_float_t*)self, other); break;
        case OBJ_TYPE_DOUBLE: obj_double_to_string((obj_double_t*)self, other); break;
        case OBJ_TYPE_SYMBOL: obj_symbol_to_string((obj_symbol_t*)self, other); break;
        case OBJ_TYPE_STRING: obj_string_to_string((obj_string_t*)self, other); break;
        case OBJ_TYPE_FILE: obj_file_to_string((obj_file_t*)self, other); break;
        case OBJ_TYPE_ENV: obj_env_to_string((obj_env_t*)self, other); break;
        case OBJ_TYPE_ARRAY: obj_array_to_string((obj_array_t*)self, other); break;
        case OBJ_TYPE_HASH_TABLE: obj_hash_table_to_string((obj_hash_table_t*)self, other); break;
        case OBJ_TYPE_FFI: obj_ffi_to_string((obj_ffi_t*)self, other); break;
        case OBJ_TYPE_MACRO: obj_macro_to_string((obj_macro_t*)self, other); break;
        case OBJ_TYPE_CLOSURE: obj_closure_to_string((obj_closure_t*)self, other); break;
        case OBJ_TYPE_PRIMITIVE: obj_primitive_to_string((obj_primitive_t*)self, other); break;
        case OBJ_TYPE_REPL: obj_repl_to_string((obj_repl_t*)self, other); break;
        default: assert(0);
    }
}

obj_ffi_t* obj_to_ffi(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_to_ffi((obj_lisp_type_t*)self);
        case OBJ_TYPE_ERROR: return obj_error_to_ffi((obj_error_t*)self);
        case OBJ_TYPE_EOF: return obj_eof_to_ffi((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return obj_nil_to_ffi((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return obj_pointer_to_ffi((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return obj_bool_to_ffi((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return obj_void_to_ffi((obj_void_t*)self);
        case OBJ_TYPE_CHAR: return obj_char_to_ffi((obj_char_t*)self);
        case OBJ_TYPE_UCHAR: return obj_uchar_to_ffi((obj_uchar_t*)self);
        case OBJ_TYPE_INT: return obj_int_to_ffi((obj_int_t*)self);
        case OBJ_TYPE_UINT: return obj_uint_to_ffi((obj_uint_t*)self);
        case OBJ_TYPE_SHORT: return obj_short_to_ffi((obj_short_t*)self);
        case OBJ_TYPE_USHORT: return obj_ushort_to_ffi((obj_ushort_t*)self);
        case OBJ_TYPE_LONG: return obj_long_to_ffi((obj_long_t*)self);
        case OBJ_TYPE_ULONG: return obj_ulong_to_ffi((obj_ulong_t*)self);
        case OBJ_TYPE_SIZE_T: return obj_size_t_to_ffi((obj_size_t_t*)self);
        case OBJ_TYPE_FLOAT: return obj_float_to_ffi((obj_float_t*)self);
        case OBJ_TYPE_DOUBLE: return obj_double_to_ffi((obj_double_t*)self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_to_ffi((obj_symbol_t*)self);
        case OBJ_TYPE_STRING: return obj_string_to_ffi((obj_string_t*)self);
        case OBJ_TYPE_FILE: return obj_file_to_ffi((obj_file_t*)self);
        case OBJ_TYPE_ENV: return obj_env_to_ffi((obj_env_t*)self);
        case OBJ_TYPE_ARRAY: return obj_array_to_ffi((obj_array_t*)self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_to_ffi((obj_hash_table_t*)self);
        case OBJ_TYPE_FFI: return obj_ffi_to_ffi((obj_ffi_t*)self);
        case OBJ_TYPE_MACRO: return obj_macro_to_ffi((obj_macro_t*)self);
        case OBJ_TYPE_CLOSURE: return obj_closure_to_ffi((obj_closure_t*)self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_to_ffi((obj_primitive_t*)self);
        case OBJ_TYPE_REPL: return obj_repl_to_ffi((obj_repl_t*)self);
        default: assert(0);
    }
}

obj_t* obj_copy(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_copy((obj_lisp_type_t*)self);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_copy((obj_error_t*)self);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_copy((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_copy((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_copy((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_copy((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_copy((obj_void_t*)self);
        case OBJ_TYPE_CHAR: return (obj_t*) obj_char_copy((obj_char_t*)self);
        case OBJ_TYPE_UCHAR: return (obj_t*) obj_uchar_copy((obj_uchar_t*)self);
        case OBJ_TYPE_INT: return (obj_t*) obj_int_copy((obj_int_t*)self);
        case OBJ_TYPE_UINT: return (obj_t*) obj_uint_copy((obj_uint_t*)self);
        case OBJ_TYPE_SHORT: return (obj_t*) obj_short_copy((obj_short_t*)self);
        case OBJ_TYPE_USHORT: return (obj_t*) obj_ushort_copy((obj_ushort_t*)self);
        case OBJ_TYPE_LONG: return (obj_t*) obj_long_copy((obj_long_t*)self);
        case OBJ_TYPE_ULONG: return (obj_t*) obj_ulong_copy((obj_ulong_t*)self);
        case OBJ_TYPE_SIZE_T: return (obj_t*) obj_size_t_copy((obj_size_t_t*)self);
        case OBJ_TYPE_FLOAT: return (obj_t*) obj_float_copy((obj_float_t*)self);
        case OBJ_TYPE_DOUBLE: return (obj_t*) obj_double_copy((obj_double_t*)self);
        case OBJ_TYPE_SYMBOL: return (obj_t*) obj_symbol_copy((obj_symbol_t*)self);
        case OBJ_TYPE_STRING: return (obj_t*) obj_string_copy((obj_string_t*)self);
        case OBJ_TYPE_FILE: return (obj_t*) obj_file_copy((obj_file_t*)self);
        case OBJ_TYPE_ENV: return (obj_t*) obj_env_copy((obj_env_t*)self);
        case OBJ_TYPE_ARRAY: return (obj_t*) obj_array_copy((obj_array_t*)self);
        case OBJ_TYPE_HASH_TABLE: return (obj_t*) obj_hash_table_copy((obj_hash_table_t*)self);
        case OBJ_TYPE_FFI: return (obj_t*) obj_ffi_copy((obj_ffi_t*)self);
        case OBJ_TYPE_MACRO: return (obj_t*) obj_macro_copy((obj_macro_t*)self);
        case OBJ_TYPE_CLOSURE: return (obj_t*) obj_closure_copy((obj_closure_t*)self);
        case OBJ_TYPE_PRIMITIVE: return (obj_t*) obj_primitive_copy((obj_primitive_t*)self);
        case OBJ_TYPE_REPL: return (obj_t*) obj_repl_copy((obj_repl_t*)self);
        default: assert(0);
    }
}

bool obj_equal(const obj_t* self, const obj_t* other) {
    if (self->type != other->type) {
        return false;
    }
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_equal((obj_lisp_type_t*)self, (obj_lisp_type_t*)other);
        case OBJ_TYPE_ERROR: return obj_error_equal((obj_error_t*)self, (obj_error_t*)other);
        case OBJ_TYPE_EOF: return obj_eof_equal((obj_eof_t*)self, (obj_eof_t*)other);
        case OBJ_TYPE_NIL: return obj_nil_equal((obj_nil_t*)self, (obj_nil_t*)other);
        case OBJ_TYPE_POINTER: return obj_pointer_equal((obj_pointer_t*)self, (obj_pointer_t*)other);
        case OBJ_TYPE_BOOL: return obj_bool_equal((obj_bool_t*)self, (obj_bool_t*)other);
        case OBJ_TYPE_VOID: return obj_void_equal((obj_void_t*)self, (obj_void_t*)other);
        case OBJ_TYPE_CHAR: return obj_char_equal((obj_char_t*)self, (obj_char_t*)other);
        case OBJ_TYPE_UCHAR: return obj_uchar_equal((obj_uchar_t*)self, (obj_uchar_t*)other);
        case OBJ_TYPE_INT: return obj_int_equal((obj_int_t*)self, (obj_int_t*)other);
        case OBJ_TYPE_UINT: return obj_uint_equal((obj_uint_t*)self, (obj_uint_t*)other);
        case OBJ_TYPE_SHORT: return obj_short_equal((obj_short_t*)self, (obj_short_t*)other);
        case OBJ_TYPE_USHORT: return obj_ushort_equal((obj_ushort_t*)self, (obj_ushort_t*)other);
        case OBJ_TYPE_LONG: return obj_long_equal((obj_long_t*)self, (obj_long_t*)other);
        case OBJ_TYPE_ULONG: return obj_ulong_equal((obj_ulong_t*)self, (obj_ulong_t*)other);
        case OBJ_TYPE_SIZE_T: return obj_size_t_equal((obj_size_t_t*)self, (obj_size_t_t*)other);
        case OBJ_TYPE_FLOAT: return obj_float_equal((obj_float_t*)self, (obj_float_t*)other);
        case OBJ_TYPE_DOUBLE: return obj_double_equal((obj_double_t*)self, (obj_double_t*)other);
        case OBJ_TYPE_SYMBOL: return obj_symbol_equal((obj_symbol_t*)self, (obj_symbol_t*)other);
        case OBJ_TYPE_STRING: return obj_string_equal((obj_string_t*)self, (obj_string_t*)other);
        case OBJ_TYPE_FILE: return obj_file_equal((obj_file_t*)self, (obj_file_t*)other);
        case OBJ_TYPE_ENV: return obj_env_equal((obj_env_t*)self, (obj_env_t*)other);
        case OBJ_TYPE_ARRAY: return obj_array_equal((obj_array_t*)self, (obj_array_t*)other);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_equal((obj_hash_table_t*)self, (obj_hash_table_t*)other);
        case OBJ_TYPE_FFI: return obj_ffi_equal((obj_ffi_t*)self, (obj_ffi_t*)other);
        case OBJ_TYPE_MACRO: return obj_macro_equal((obj_macro_t*)self, (obj_macro_t*)other);
        case OBJ_TYPE_CLOSURE: return obj_closure_equal((obj_closure_t*)self, (obj_closure_t*)other);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_equal((obj_primitive_t*)self, (obj_primitive_t*)other);
        case OBJ_TYPE_REPL: return obj_repl_equal((obj_repl_t*)self, (obj_repl_t*)other);
        default: assert(0);
    }
}

size_t obj_hash(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_hash((obj_lisp_type_t*)self);
        case OBJ_TYPE_ERROR: return obj_error_hash((obj_error_t*)self);
        case OBJ_TYPE_EOF: return obj_eof_hash((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return obj_nil_hash((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return obj_pointer_hash((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return obj_bool_hash((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return obj_void_hash((obj_void_t*)self);
        case OBJ_TYPE_CHAR: return obj_char_hash((obj_char_t*)self);
        case OBJ_TYPE_UCHAR: return obj_uchar_hash((obj_uchar_t*)self);
        case OBJ_TYPE_INT: return obj_int_hash((obj_int_t*)self);
        case OBJ_TYPE_UINT: return obj_uint_hash((obj_uint_t*)self);
        case OBJ_TYPE_SHORT: return obj_short_hash((obj_short_t*)self);
        case OBJ_TYPE_USHORT: return obj_ushort_hash((obj_ushort_t*)self);
        case OBJ_TYPE_LONG: return obj_long_hash((obj_long_t*)self);
        case OBJ_TYPE_ULONG: return obj_ulong_hash((obj_ulong_t*)self);
        case OBJ_TYPE_SIZE_T: return obj_size_t_hash((obj_size_t_t*)self);
        case OBJ_TYPE_FLOAT: return obj_float_hash((obj_float_t*)self);
        case OBJ_TYPE_DOUBLE: return obj_double_hash((obj_double_t*)self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_hash((obj_symbol_t*)self);
        case OBJ_TYPE_STRING: return obj_string_hash((obj_string_t*)self);
        case OBJ_TYPE_FILE: return obj_file_hash((obj_file_t*)self);
        case OBJ_TYPE_ENV: return obj_env_hash((obj_env_t*)self);
        case OBJ_TYPE_ARRAY: return obj_array_hash((obj_array_t*)self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_hash((obj_hash_table_t*)self);
        case OBJ_TYPE_FFI: return obj_ffi_hash((obj_ffi_t*)self);
        case OBJ_TYPE_MACRO: return obj_macro_hash((obj_macro_t*)self);
        case OBJ_TYPE_CLOSURE: return obj_closure_hash((obj_closure_t*)self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_hash((obj_primitive_t*)self);
        case OBJ_TYPE_REPL: return obj_repl_hash((obj_repl_t*)self);
        default: assert(0);
    }
}

obj_t* obj_eval(const obj_t* self, obj_hash_table_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_eval((obj_lisp_type_t*)self, env);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_eval((obj_error_t*)self, env);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_eval((obj_eof_t*)self, env);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_eval((obj_nil_t*)self, env);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_eval((obj_pointer_t*)self, env);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_eval((obj_bool_t*)self, env);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_eval((obj_void_t*)self, env);
        case OBJ_TYPE_CHAR: return (obj_t*) obj_char_eval((obj_char_t*)self, env);
        case OBJ_TYPE_UCHAR: return (obj_t*) obj_uchar_eval((obj_uchar_t*)self, env);
        case OBJ_TYPE_INT: return (obj_t*) obj_int_eval((obj_int_t*)self, env);
        case OBJ_TYPE_UINT: return (obj_t*) obj_uint_eval((obj_uint_t*)self, env);
        case OBJ_TYPE_SHORT: return (obj_t*) obj_short_eval((obj_short_t*)self, env);
        case OBJ_TYPE_USHORT: return (obj_t*) obj_ushort_eval((obj_ushort_t*)self, env);
        case OBJ_TYPE_LONG: return (obj_t*) obj_long_eval((obj_long_t*)self, env);
        case OBJ_TYPE_ULONG: return (obj_t*) obj_ulong_eval((obj_ulong_t*)self, env);
        case OBJ_TYPE_SIZE_T: return (obj_t*) obj_size_t_eval((obj_size_t_t*)self, env);
        case OBJ_TYPE_FLOAT: return (obj_t*) obj_float_eval((obj_float_t*)self, env);
        case OBJ_TYPE_DOUBLE: return (obj_t*) obj_double_eval((obj_double_t*)self, env);
        case OBJ_TYPE_SYMBOL: return (obj_t*) obj_symbol_eval((obj_symbol_t*)self, env);
        case OBJ_TYPE_STRING: return (obj_t*) obj_string_eval((obj_string_t*)self, env);
        case OBJ_TYPE_FILE: return (obj_t*) obj_file_eval((obj_file_t*)self, env);
        case OBJ_TYPE_ENV: return (obj_t*) obj_env_eval((obj_env_t*)self, env);
        case OBJ_TYPE_ARRAY: return (obj_t*) obj_array_eval((obj_array_t*)self, env);
        case OBJ_TYPE_HASH_TABLE: return (obj_t*) obj_hash_table_eval((obj_hash_table_t*)self, env);
        case OBJ_TYPE_FFI: return (obj_t*) obj_ffi_eval((obj_ffi_t*)self, env);
        case OBJ_TYPE_MACRO: return (obj_t*) obj_macro_eval((obj_macro_t*)self, env);
        case OBJ_TYPE_CLOSURE: return (obj_t*) obj_closure_eval((obj_closure_t*)self, env);
        case OBJ_TYPE_PRIMITIVE: return (obj_t*) obj_primitive_eval((obj_primitive_t*)self, env);
        case OBJ_TYPE_REPL: return (obj_t*) obj_repl_eval((obj_repl_t*)self, env);
        default: assert(0);
    }
}

obj_t* obj_apply(const obj_t* self, obj_array_t* args, obj_hash_table_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_apply((obj_lisp_type_t*)self, args, env);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_apply((obj_error_t*)self, args, env);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_apply((obj_eof_t*)self, args, env);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_apply((obj_nil_t*)self, args, env);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_apply((obj_pointer_t*)self, args, env);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_apply((obj_bool_t*)self, args, env);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_apply((obj_void_t*)self, args, env);
        case OBJ_TYPE_CHAR: return (obj_t*) obj_char_apply((obj_char_t*)self, args, env);
        case OBJ_TYPE_UCHAR: return (obj_t*) obj_uchar_apply((obj_uchar_t*)self, args, env);
        case OBJ_TYPE_INT: return (obj_t*) obj_int_apply((obj_int_t*)self, args, env);
        case OBJ_TYPE_UINT: return (obj_t*) obj_uint_apply((obj_uint_t*)self, args, env);
        case OBJ_TYPE_SHORT: return (obj_t*) obj_short_apply((obj_short_t*)self, args, env);
        case OBJ_TYPE_USHORT: return (obj_t*) obj_ushort_apply((obj_ushort_t*)self, args, env);
        case OBJ_TYPE_LONG: return (obj_t*) obj_long_apply((obj_long_t*)self, args, env);
        case OBJ_TYPE_ULONG: return (obj_t*) obj_ulong_apply((obj_ulong_t*)self, args, env);
        case OBJ_TYPE_SIZE_T: return (obj_t*) obj_size_t_apply((obj_size_t_t*)self, args, env);
        case OBJ_TYPE_FLOAT: return (obj_t*) obj_float_apply((obj_float_t*)self, args, env);
        case OBJ_TYPE_DOUBLE: return (obj_t*) obj_double_apply((obj_double_t*)self, args, env);
        case OBJ_TYPE_SYMBOL: return (obj_t*) obj_symbol_apply((obj_symbol_t*)self, args, env);
        case OBJ_TYPE_STRING: return (obj_t*) obj_string_apply((obj_string_t*)self, args, env);
        case OBJ_TYPE_FILE: return (obj_t*) obj_file_apply((obj_file_t*)self, args, env);
        case OBJ_TYPE_ENV: return (obj_t*) obj_env_apply((obj_env_t*)self, args, env);
        case OBJ_TYPE_ARRAY: return (obj_t*) obj_array_apply((obj_array_t*)self, args, env);
        case OBJ_TYPE_HASH_TABLE: return (obj_t*) obj_hash_table_apply((obj_hash_table_t*)self, args, env);
        case OBJ_TYPE_FFI: return (obj_t*) obj_ffi_apply((obj_ffi_t*)self, args, env);
        case OBJ_TYPE_MACRO: return (obj_t*) obj_macro_apply((obj_macro_t*)self, args, env);
        case OBJ_TYPE_CLOSURE: return (obj_t*) obj_closure_apply((obj_closure_t*)self, args, env);
        case OBJ_TYPE_PRIMITIVE: return (obj_t*) obj_primitive_apply((obj_primitive_t*)self, args, env);
        case OBJ_TYPE_REPL: return (obj_t*) obj_repl_apply((obj_repl_t*)self, args, env);
        default: assert(0);
    }
}
