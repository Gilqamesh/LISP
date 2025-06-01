#include "obj.h"

#include "obj_lisp_type.h"
#include "obj_cons.h"
#include "obj_error.h"
#include "obj_eof.h"
#include "obj_nil.h"
#include "obj_pointer.h"
#include "obj_bool.h"
#include "obj_void.h"
#include "obj_i8.h"
#include "obj_u8.h"
#include "obj_i16.h"
#include "obj_u16.h"
#include "obj_i32.h"
#include "obj_u32.h"
#include "obj_i64.h"
#include "obj_u64.h"
#include "obj_r32.h"
#include "obj_r64.h"
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
#include "obj_reader.h"

const char* obj_type_to_string(obj_type_t type) {
    switch (type) {
        case OBJ_TYPE_LISP_TYPE: return "lisp_type";
        case OBJ_TYPE_CONS: return "cons";
        case OBJ_TYPE_ERROR: return "error";
        case OBJ_TYPE_EOF: return "eof";
        case OBJ_TYPE_NIL: return "nil";
        case OBJ_TYPE_POINTER: return "pointer";
        case OBJ_TYPE_BOOL: return "bool";
        case OBJ_TYPE_VOID: return "void";
        case OBJ_TYPE_I8: return "i8";
        case OBJ_TYPE_U8: return "u8";
        case OBJ_TYPE_I16: return "i16";
        case OBJ_TYPE_U16: return "u16";
        case OBJ_TYPE_I32: return "i32";
        case OBJ_TYPE_U32: return "u32";
        case OBJ_TYPE_I64: return "i64";
        case OBJ_TYPE_U64: return "u64";
        case OBJ_TYPE_R32: return "r32";
        case OBJ_TYPE_R64: return "r64";
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
        case OBJ_TYPE_READER: return "reader";
        default: assert(0);
    }
}

void obj_init(obj_t* self, obj_type_t type) {
    self->type = type;
}

void obj_delete(obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: obj_lisp_type_delete((obj_lisp_type_t*)self); break;
        case OBJ_TYPE_CONS: obj_cons_delete((obj_cons_t*)self); break;
        case OBJ_TYPE_ERROR: obj_error_delete((obj_error_t*)self); break;
        case OBJ_TYPE_EOF: obj_eof_delete((obj_eof_t*)self); break;
        case OBJ_TYPE_NIL: obj_nil_delete((obj_nil_t*)self); break;
        case OBJ_TYPE_POINTER: obj_pointer_delete((obj_pointer_t*)self); break;
        case OBJ_TYPE_BOOL: obj_bool_delete((obj_bool_t*)self); break;
        case OBJ_TYPE_VOID: obj_void_delete((obj_void_t*)self); break;
        case OBJ_TYPE_I8: obj_i8_delete((obj_i8_t*)self); break;
        case OBJ_TYPE_U8: obj_u8_delete((obj_u8_t*)self); break;
        case OBJ_TYPE_I16: obj_i16_delete((obj_i16_t*)self); break;
        case OBJ_TYPE_U16: obj_u16_delete((obj_u16_t*)self); break;
        case OBJ_TYPE_I32: obj_i32_delete((obj_i32_t*)self); break;
        case OBJ_TYPE_U32: obj_u32_delete((obj_u32_t*)self); break;
        case OBJ_TYPE_I64: obj_i64_delete((obj_i64_t*)self); break;
        case OBJ_TYPE_U64: obj_u64_delete((obj_u64_t*)self); break;
        case OBJ_TYPE_R32: obj_r32_delete((obj_r32_t*)self); break;
        case OBJ_TYPE_R64: obj_r64_delete((obj_r64_t*)self); break;
        case OBJ_TYPE_SYMBOL: obj_symbol_delete((obj_symbol_t*)self); break;
        case OBJ_TYPE_STRING: obj_string_delete((obj_string_t*)self); break;
        case OBJ_TYPE_FILE: obj_file_delete((obj_file_t*)self); break;
        case OBJ_TYPE_ENV: obj_env_delete((obj_env_t*)self); break;
        case OBJ_TYPE_ARRAY: obj_array_delete((obj_array_t*)self); break;
        case OBJ_TYPE_HASH_TABLE: obj_hash_table_delete((obj_hash_table_t*)self); break;
        case OBJ_TYPE_FFI: obj_ffi_delete((obj_ffi_t*)self); break;
        case OBJ_TYPE_MACRO: obj_macro_delete((obj_macro_t*)self); break;
        case OBJ_TYPE_CLOSURE: obj_closure_delete((obj_closure_t*)self); break;
        case OBJ_TYPE_PRIMITIVE: obj_primitive_delete((obj_primitive_t*)self); break;
        case OBJ_TYPE_REPL: obj_repl_delete((obj_repl_t*)self); break;
        case OBJ_TYPE_READER: obj_reader_delete((obj_reader_t*)self); break;
        default: assert(0);
    }
}

obj_type_t obj_get_type(const obj_t* self) {
    return self->type;
}

void obj_to_string(const obj_t* self, obj_string_t* other) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: obj_lisp_type_to_string((obj_lisp_type_t*)self, other); break;
        case OBJ_TYPE_CONS: obj_cons_to_string((obj_cons_t*)self, other); break;
        case OBJ_TYPE_ERROR: obj_error_to_string((obj_error_t*)self, other); break;
        case OBJ_TYPE_EOF: obj_eof_to_string((obj_eof_t*)self, other); break;
        case OBJ_TYPE_NIL: obj_nil_to_string((obj_nil_t*)self, other); break;
        case OBJ_TYPE_POINTER: obj_pointer_to_string((obj_pointer_t*)self, other); break;
        case OBJ_TYPE_BOOL: obj_bool_to_string((obj_bool_t*)self, other); break;
        case OBJ_TYPE_VOID: obj_void_to_string((obj_void_t*)self, other); break;
        case OBJ_TYPE_I8: obj_i8_to_string((obj_i8_t*)self, other); break;
        case OBJ_TYPE_U8: obj_u8_to_string((obj_u8_t*)self, other); break;
        case OBJ_TYPE_I16: obj_i16_to_string((obj_i16_t*)self, other); break;
        case OBJ_TYPE_U16: obj_u16_to_string((obj_u16_t*)self, other); break;
        case OBJ_TYPE_I32: obj_i32_to_string((obj_i32_t*)self, other); break;
        case OBJ_TYPE_U32: obj_u32_to_string((obj_u32_t*)self, other); break;
        case OBJ_TYPE_I64: obj_i64_to_string((obj_i64_t*)self, other); break;
        case OBJ_TYPE_U64: obj_u64_to_string((obj_u64_t*)self, other); break;
        case OBJ_TYPE_R32: obj_r32_to_string((obj_r32_t*)self, other); break;
        case OBJ_TYPE_R64: obj_r64_to_string((obj_r64_t*)self, other); break;
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
        case OBJ_TYPE_READER: obj_reader_to_string((obj_reader_t*)self, other); break;
        default: assert(0);
    }
}

obj_ffi_t* obj_to_ffi(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_to_ffi((obj_lisp_type_t*)self);
        case OBJ_TYPE_CONS: return obj_cons_to_ffi((obj_cons_t*)self);
        case OBJ_TYPE_ERROR: return obj_error_to_ffi((obj_error_t*)self);
        case OBJ_TYPE_EOF: return obj_eof_to_ffi((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return obj_nil_to_ffi((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return obj_pointer_to_ffi((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return obj_bool_to_ffi((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return obj_void_to_ffi((obj_void_t*)self);
        case OBJ_TYPE_I8: return obj_i8_to_ffi((obj_i8_t*)self);
        case OBJ_TYPE_U8: return obj_u8_to_ffi((obj_u8_t*)self);
        case OBJ_TYPE_I16: return obj_i16_to_ffi((obj_i16_t*)self);
        case OBJ_TYPE_U16: return obj_u16_to_ffi((obj_u16_t*)self);
        case OBJ_TYPE_I32: return obj_i32_to_ffi((obj_i32_t*)self);
        case OBJ_TYPE_U32: return obj_u32_to_ffi((obj_u32_t*)self);
        case OBJ_TYPE_I64: return obj_i64_to_ffi((obj_i64_t*)self);
        case OBJ_TYPE_U64: return obj_u64_to_ffi((obj_u64_t*)self);
        case OBJ_TYPE_R32: return obj_r32_to_ffi((obj_r32_t*)self);
        case OBJ_TYPE_R64: return obj_r64_to_ffi((obj_r64_t*)self);
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
        case OBJ_TYPE_READER: return obj_reader_to_ffi((obj_reader_t*)self);
        default: assert(0);
    }
}

obj_t* obj_copy(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_copy((obj_lisp_type_t*)self);
        case OBJ_TYPE_CONS: return (obj_t*) obj_cons_copy((obj_cons_t*)self);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_copy((obj_error_t*)self);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_copy((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_copy((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_copy((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_copy((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_copy((obj_void_t*)self);
        case OBJ_TYPE_I8: return (obj_t*) obj_i8_copy((obj_i8_t*)self);
        case OBJ_TYPE_U8: return (obj_t*) obj_u8_copy((obj_u8_t*)self);
        case OBJ_TYPE_I16: return (obj_t*) obj_i16_copy((obj_i16_t*)self);
        case OBJ_TYPE_U16: return (obj_t*) obj_u16_copy((obj_u16_t*)self);
        case OBJ_TYPE_I32: return (obj_t*) obj_i32_copy((obj_i32_t*)self);
        case OBJ_TYPE_U32: return (obj_t*) obj_u32_copy((obj_u32_t*)self);
        case OBJ_TYPE_I64: return (obj_t*) obj_i64_copy((obj_i64_t*)self);
        case OBJ_TYPE_U64: return (obj_t*) obj_u64_copy((obj_u64_t*)self);
        case OBJ_TYPE_R32: return (obj_t*) obj_r32_copy((obj_r32_t*)self);
        case OBJ_TYPE_R64: return (obj_t*) obj_r64_copy((obj_r64_t*)self);
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
        case OBJ_TYPE_READER: return (obj_t*) obj_reader_copy((obj_reader_t*)self);
        default: assert(0);
    }
}

bool obj_equal(const obj_t* self, const obj_t* other) {
    if (self->type != other->type) {
        return false;
    }
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_equal((obj_lisp_type_t*)self, (obj_lisp_type_t*)other);
        case OBJ_TYPE_CONS: return obj_cons_equal((obj_cons_t*)self, (obj_cons_t*)other);
        case OBJ_TYPE_ERROR: return obj_error_equal((obj_error_t*)self, (obj_error_t*)other);
        case OBJ_TYPE_EOF: return obj_eof_equal((obj_eof_t*)self, (obj_eof_t*)other);
        case OBJ_TYPE_NIL: return obj_nil_equal((obj_nil_t*)self, (obj_nil_t*)other);
        case OBJ_TYPE_POINTER: return obj_pointer_equal((obj_pointer_t*)self, (obj_pointer_t*)other);
        case OBJ_TYPE_BOOL: return obj_bool_equal((obj_bool_t*)self, (obj_bool_t*)other);
        case OBJ_TYPE_VOID: return obj_void_equal((obj_void_t*)self, (obj_void_t*)other);
        case OBJ_TYPE_I8: return obj_i8_equal((obj_i8_t*)self, (obj_i8_t*)other);
        case OBJ_TYPE_U8: return obj_u8_equal((obj_u8_t*)self, (obj_u8_t*)other);
        case OBJ_TYPE_I16: return obj_i16_equal((obj_i16_t*)self, (obj_i16_t*)other);
        case OBJ_TYPE_U16: return obj_u16_equal((obj_u16_t*)self, (obj_u16_t*)other);
        case OBJ_TYPE_I32: return obj_i32_equal((obj_i32_t*)self, (obj_i32_t*)other);
        case OBJ_TYPE_U32: return obj_u32_equal((obj_u32_t*)self, (obj_u32_t*)other);
        case OBJ_TYPE_I64: return obj_i64_equal((obj_i64_t*)self, (obj_i64_t*)other);
        case OBJ_TYPE_U64: return obj_u64_equal((obj_u64_t*)self, (obj_u64_t*)other);
        case OBJ_TYPE_R32: return obj_r32_equal((obj_r32_t*)self, (obj_r32_t*)other);
        case OBJ_TYPE_R64: return obj_r64_equal((obj_r64_t*)self, (obj_r64_t*)other);
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
        case OBJ_TYPE_READER: return obj_reader_equal((obj_reader_t*)self, (obj_reader_t*)other);
        default: assert(0);
    }
}

bool obj_is_truthy(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_is_truthy((obj_lisp_type_t*)self);
        case OBJ_TYPE_CONS: return obj_cons_is_truthy((obj_cons_t*)self);
        case OBJ_TYPE_ERROR: return obj_error_is_truthy((obj_error_t*)self);
        case OBJ_TYPE_EOF: return obj_eof_is_truthy((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return obj_nil_is_truthy((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return obj_pointer_is_truthy((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return obj_bool_is_truthy((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return obj_void_is_truthy((obj_void_t*)self);
        case OBJ_TYPE_I8: return obj_i8_is_truthy((obj_i8_t*)self);
        case OBJ_TYPE_U8: return obj_u8_is_truthy((obj_u8_t*)self);
        case OBJ_TYPE_I16: return obj_i16_is_truthy((obj_i16_t*)self);
        case OBJ_TYPE_U16: return obj_u16_is_truthy((obj_u16_t*)self);
        case OBJ_TYPE_I32: return obj_i32_is_truthy((obj_i32_t*)self);
        case OBJ_TYPE_U32: return obj_u32_is_truthy((obj_u32_t*)self);
        case OBJ_TYPE_I64: return obj_i64_is_truthy((obj_i64_t*)self);
        case OBJ_TYPE_U64: return obj_u64_is_truthy((obj_u64_t*)self);
        case OBJ_TYPE_R32: return obj_r32_is_truthy((obj_r32_t*)self);
        case OBJ_TYPE_R64: return obj_r64_is_truthy((obj_r64_t*)self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_is_truthy((obj_symbol_t*)self);
        case OBJ_TYPE_STRING: return obj_string_is_truthy((obj_string_t*)self);
        case OBJ_TYPE_FILE: return obj_file_is_truthy((obj_file_t*)self);
        case OBJ_TYPE_ENV: return obj_env_is_truthy((obj_env_t*)self);
        case OBJ_TYPE_ARRAY: return obj_array_is_truthy((obj_array_t*)self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_is_truthy((obj_hash_table_t*)self);
        case OBJ_TYPE_FFI: return obj_ffi_is_truthy((obj_ffi_t*)self);
        case OBJ_TYPE_MACRO: return obj_macro_is_truthy((obj_macro_t*)self);
        case OBJ_TYPE_CLOSURE: return obj_closure_is_truthy((obj_closure_t*)self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_is_truthy((obj_primitive_t*)self);
        case OBJ_TYPE_REPL: return obj_repl_is_truthy((obj_repl_t*)self);
        case OBJ_TYPE_READER: return obj_reader_is_truthy((obj_reader_t*)self);
        default: assert(0);
    }
}

bool obj_is_eq(const obj_t* self, const obj_t* other) {
    return self == other;
}

size_t obj_hash(const obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_hash((obj_lisp_type_t*)self);
        case OBJ_TYPE_CONS: return obj_cons_hash((obj_cons_t*)self);
        case OBJ_TYPE_ERROR: return obj_error_hash((obj_error_t*)self);
        case OBJ_TYPE_EOF: return obj_eof_hash((obj_eof_t*)self);
        case OBJ_TYPE_NIL: return obj_nil_hash((obj_nil_t*)self);
        case OBJ_TYPE_POINTER: return obj_pointer_hash((obj_pointer_t*)self);
        case OBJ_TYPE_BOOL: return obj_bool_hash((obj_bool_t*)self);
        case OBJ_TYPE_VOID: return obj_void_hash((obj_void_t*)self);
        case OBJ_TYPE_I8: return obj_i8_hash((obj_i8_t*)self);
        case OBJ_TYPE_U8: return obj_u8_hash((obj_u8_t*)self);
        case OBJ_TYPE_I16: return obj_i16_hash((obj_i16_t*)self);
        case OBJ_TYPE_U16: return obj_u16_hash((obj_u16_t*)self);
        case OBJ_TYPE_I32: return obj_i32_hash((obj_i32_t*)self);
        case OBJ_TYPE_U32: return obj_u32_hash((obj_u32_t*)self);
        case OBJ_TYPE_I64: return obj_i64_hash((obj_i64_t*)self);
        case OBJ_TYPE_U64: return obj_u64_hash((obj_u64_t*)self);
        case OBJ_TYPE_R32: return obj_r32_hash((obj_r32_t*)self);
        case OBJ_TYPE_R64: return obj_r64_hash((obj_r64_t*)self);
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
        case OBJ_TYPE_READER: return obj_reader_hash((obj_reader_t*)self);
        default: assert(0);
    }
}

obj_t* obj_eval(const obj_t* self, obj_env_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_eval((obj_lisp_type_t*)self, env);
        case OBJ_TYPE_CONS: return (obj_t*) obj_cons_eval((obj_cons_t*)self, env);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_eval((obj_error_t*)self, env);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_eval((obj_eof_t*)self, env);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_eval((obj_nil_t*)self, env);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_eval((obj_pointer_t*)self, env);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_eval((obj_bool_t*)self, env);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_eval((obj_void_t*)self, env);
        case OBJ_TYPE_I8: return (obj_t*) obj_i8_eval((obj_i8_t*)self, env);
        case OBJ_TYPE_U8: return (obj_t*) obj_u8_eval((obj_u8_t*)self, env);
        case OBJ_TYPE_I16: return (obj_t*) obj_i16_eval((obj_i16_t*)self, env);
        case OBJ_TYPE_U16: return (obj_t*) obj_u16_eval((obj_u16_t*)self, env);
        case OBJ_TYPE_I32: return (obj_t*) obj_i32_eval((obj_i32_t*)self, env);
        case OBJ_TYPE_U32: return (obj_t*) obj_u32_eval((obj_u32_t*)self, env);
        case OBJ_TYPE_I64: return (obj_t*) obj_i64_eval((obj_i64_t*)self, env);
        case OBJ_TYPE_U64: return (obj_t*) obj_u64_eval((obj_u64_t*)self, env);
        case OBJ_TYPE_R32: return (obj_t*) obj_r32_eval((obj_r32_t*)self, env);
        case OBJ_TYPE_R64: return (obj_t*) obj_r64_eval((obj_r64_t*)self, env);
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
        case OBJ_TYPE_READER: return (obj_t*) obj_reader_eval((obj_reader_t*)self, env);
        default: assert(0);
    }
}

obj_t* obj_apply(const obj_t* self, obj_t* args, obj_env_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return (obj_t*) obj_lisp_type_apply((obj_lisp_type_t*)self, args, env);
        case OBJ_TYPE_CONS: return (obj_t*) obj_cons_apply((obj_cons_t*)self, args, env);
        case OBJ_TYPE_ERROR: return (obj_t*) obj_error_apply((obj_error_t*)self, args, env);
        case OBJ_TYPE_EOF: return (obj_t*) obj_eof_apply((obj_eof_t*)self, args, env);
        case OBJ_TYPE_NIL: return (obj_t*) obj_nil_apply((obj_nil_t*)self, args, env);
        case OBJ_TYPE_POINTER: return (obj_t*) obj_pointer_apply((obj_pointer_t*)self, args, env);
        case OBJ_TYPE_BOOL: return (obj_t*) obj_bool_apply((obj_bool_t*)self, args, env);
        case OBJ_TYPE_VOID: return (obj_t*) obj_void_apply((obj_void_t*)self, args, env);
        case OBJ_TYPE_I8: return (obj_t*) obj_i8_apply((obj_i8_t*)self, args, env);
        case OBJ_TYPE_U8: return (obj_t*) obj_u8_apply((obj_u8_t*)self, args, env);
        case OBJ_TYPE_I16: return (obj_t*) obj_i16_apply((obj_i16_t*)self, args, env);
        case OBJ_TYPE_U16: return (obj_t*) obj_u16_apply((obj_u16_t*)self, args, env);
        case OBJ_TYPE_I32: return (obj_t*) obj_i32_apply((obj_i32_t*)self, args, env);
        case OBJ_TYPE_U32: return (obj_t*) obj_u32_apply((obj_u32_t*)self, args, env);
        case OBJ_TYPE_I64: return (obj_t*) obj_i64_apply((obj_i64_t*)self, args, env);
        case OBJ_TYPE_U64: return (obj_t*) obj_u64_apply((obj_u64_t*)self, args, env);
        case OBJ_TYPE_R32: return (obj_t*) obj_r32_apply((obj_r32_t*)self, args, env);
        case OBJ_TYPE_R64: return (obj_t*) obj_r64_apply((obj_r64_t*)self, args, env);
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
        case OBJ_TYPE_READER: return (obj_t*) obj_reader_apply((obj_reader_t*)self, args, env);
        default: assert(0);
    }
}
