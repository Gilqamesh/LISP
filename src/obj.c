#include "obj.h"

#include "obj_lisp_type.h"
#include "obj_cons.h"
#include "obj_error.h"
#include "obj_eof.h"
#include "obj_nil.h"
#include "obj_pointer.h"
#include "obj_bool.h"
#include "obj_void.h"
#include "obj_i32.h"
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
        case OBJ_TYPE_I32: return "i32";
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
        case OBJ_TYPE_LISP_TYPE: obj_lisp_type_delete(self); break;
        case OBJ_TYPE_CONS: obj_cons_delete(self); break;
        case OBJ_TYPE_ERROR: obj_error_delete(self); break;
        case OBJ_TYPE_EOF: obj_eof_delete(self); break;
        case OBJ_TYPE_NIL: obj_nil_delete(self); break;
        case OBJ_TYPE_POINTER: obj_pointer_delete(self); break;
        case OBJ_TYPE_BOOL: obj_bool_delete(self); break;
        case OBJ_TYPE_VOID: obj_void_delete(self); break;
        case OBJ_TYPE_I32: obj_i32_delete(self); break;
        case OBJ_TYPE_R64: obj_r64_delete(self); break;
        case OBJ_TYPE_SYMBOL: obj_symbol_delete(self); break;
        case OBJ_TYPE_STRING: obj_string_delete(self); break;
        case OBJ_TYPE_FILE: obj_file_delete(self); break;
        case OBJ_TYPE_ENV: obj_env_delete(self); break;
        case OBJ_TYPE_ARRAY: obj_array_delete(self); break;
        case OBJ_TYPE_HASH_TABLE: obj_hash_table_delete(self); break;
        case OBJ_TYPE_FFI: obj_ffi_delete(self); break;
        case OBJ_TYPE_MACRO: obj_macro_delete(self); break;
        case OBJ_TYPE_CLOSURE: obj_closure_delete(self); break;
        case OBJ_TYPE_PRIMITIVE: obj_primitive_delete(self); break;
        case OBJ_TYPE_REPL: obj_repl_delete(self); break;
        case OBJ_TYPE_READER: obj_reader_delete(self); break;
        default: assert(0);
    }
}

obj_type_t obj_get_type(obj_t* self) {
    return self->type;
}

void obj_to_string(obj_t* self, obj_t* string) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: obj_lisp_type_to_string(self, string); break;
        case OBJ_TYPE_CONS: obj_cons_to_string(self, string); break;
        case OBJ_TYPE_ERROR: obj_error_to_string(self, string); break;
        case OBJ_TYPE_EOF: obj_eof_to_string(self, string); break;
        case OBJ_TYPE_NIL: obj_nil_to_string(self, string); break;
        case OBJ_TYPE_POINTER: obj_pointer_to_string(self, string); break;
        case OBJ_TYPE_BOOL: obj_bool_to_string(self, string); break;
        case OBJ_TYPE_VOID: obj_void_to_string(self, string); break;
        case OBJ_TYPE_I32: obj_i32_to_string(self, string); break;
        case OBJ_TYPE_R64: obj_r64_to_string(self, string); break;
        case OBJ_TYPE_SYMBOL: obj_symbol_to_string(self, string); break;
        case OBJ_TYPE_STRING: obj_string_to_string(self, string); break;
        case OBJ_TYPE_FILE: obj_file_to_string(self, string); break;
        case OBJ_TYPE_ENV: obj_env_to_string(self, string); break;
        case OBJ_TYPE_ARRAY: obj_array_to_string(self, string); break;
        case OBJ_TYPE_HASH_TABLE: obj_hash_table_to_string(self, string); break;
        case OBJ_TYPE_FFI: obj_ffi_to_string(self, string); break;
        case OBJ_TYPE_MACRO: obj_macro_to_string(self, string); break;
        case OBJ_TYPE_CLOSURE: obj_closure_to_string(self, string); break;
        case OBJ_TYPE_PRIMITIVE: obj_primitive_to_string(self, string); break;
        case OBJ_TYPE_REPL: obj_repl_to_string(self, string); break;
        case OBJ_TYPE_READER: obj_reader_to_string(self, string); break;
        default: assert(0);
    }
}

ffi_type* obj_to_ffi(obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_to_ffi(self);
        case OBJ_TYPE_CONS: return obj_cons_to_ffi(self);
        case OBJ_TYPE_ERROR: return obj_error_to_ffi(self);
        case OBJ_TYPE_EOF: return obj_eof_to_ffi(self);
        case OBJ_TYPE_NIL: return obj_nil_to_ffi(self);
        case OBJ_TYPE_POINTER: return obj_pointer_to_ffi(self);
        case OBJ_TYPE_BOOL: return obj_bool_to_ffi(self);
        case OBJ_TYPE_VOID: return obj_void_to_ffi(self);
        case OBJ_TYPE_I32: return obj_i32_to_ffi(self);
        case OBJ_TYPE_R64: return obj_r64_to_ffi(self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_to_ffi(self);
        case OBJ_TYPE_STRING: return obj_string_to_ffi(self);
        case OBJ_TYPE_FILE: return obj_file_to_ffi(self);
        case OBJ_TYPE_ENV: return obj_env_to_ffi(self);
        case OBJ_TYPE_ARRAY: return obj_array_to_ffi(self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_to_ffi(self);
        case OBJ_TYPE_FFI: return obj_ffi_to_ffi(self);
        case OBJ_TYPE_MACRO: return obj_macro_to_ffi(self);
        case OBJ_TYPE_CLOSURE: return obj_closure_to_ffi(self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_to_ffi(self);
        case OBJ_TYPE_REPL: return obj_repl_to_ffi(self);
        case OBJ_TYPE_READER: return obj_reader_to_ffi(self);
        default: assert(0);
    }
}

obj_t* obj_copy(obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_copy(self);
        case OBJ_TYPE_CONS: return obj_cons_copy(self);
        case OBJ_TYPE_ERROR: return obj_error_copy(self);
        case OBJ_TYPE_EOF: return obj_eof_copy(self);
        case OBJ_TYPE_NIL: return obj_nil_copy(self);
        case OBJ_TYPE_POINTER: return obj_pointer_copy(self);
        case OBJ_TYPE_BOOL: return obj_bool_copy(self);
        case OBJ_TYPE_VOID: return obj_void_copy(self);
        case OBJ_TYPE_I32: return obj_i32_copy(self);
        case OBJ_TYPE_R64: return obj_r64_copy(self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_copy(self);
        case OBJ_TYPE_STRING: return obj_string_copy(self);
        case OBJ_TYPE_FILE: return obj_file_copy(self);
        case OBJ_TYPE_ENV: return obj_env_copy(self);
        case OBJ_TYPE_ARRAY: return obj_array_copy(self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_copy(self);
        case OBJ_TYPE_FFI: return obj_ffi_copy(self);
        case OBJ_TYPE_MACRO: return obj_macro_copy(self);
        case OBJ_TYPE_CLOSURE: return obj_closure_copy(self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_copy(self);
        case OBJ_TYPE_REPL: return obj_repl_copy(self);
        case OBJ_TYPE_READER: return obj_reader_copy(self);
        default: assert(0);
    }
}

bool obj_is_equal(obj_t* self, obj_t* other) {
    if (self->type != other->type) {
        return false;
    }
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_is_equal(self, other);
        case OBJ_TYPE_CONS: return obj_cons_is_equal(self, other);
        case OBJ_TYPE_ERROR: return obj_error_is_equal(self, other);
        case OBJ_TYPE_EOF: return obj_eof_is_equal(self, other);
        case OBJ_TYPE_NIL: return obj_nil_is_equal(self, other);
        case OBJ_TYPE_POINTER: return obj_pointer_is_equal(self, other);
        case OBJ_TYPE_BOOL: return obj_bool_is_equal(self, other);
        case OBJ_TYPE_VOID: return obj_void_is_equal(self, other);
        case OBJ_TYPE_I32: return obj_i32_is_equal(self, other);
        case OBJ_TYPE_R64: return obj_r64_is_equal(self, other);
        case OBJ_TYPE_SYMBOL: return obj_symbol_is_equal(self, other);
        case OBJ_TYPE_STRING: return obj_string_is_equal(self, other);
        case OBJ_TYPE_FILE: return obj_file_is_equal(self, other);
        case OBJ_TYPE_ENV: return obj_env_is_equal(self, other);
        case OBJ_TYPE_ARRAY: return obj_array_is_equal(self, other);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_is_equal(self, other);
        case OBJ_TYPE_FFI: return obj_ffi_is_equal(self, other);
        case OBJ_TYPE_MACRO: return obj_macro_is_equal(self, other);
        case OBJ_TYPE_CLOSURE: return obj_closure_is_equal(self, other);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_is_equal(self, other);
        case OBJ_TYPE_REPL: return obj_repl_is_equal(self, other);
        case OBJ_TYPE_READER: return obj_reader_is_equal(self, other);
        default: assert(0);
    }
}

bool obj_is_truthy(obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_is_truthy(self);
        case OBJ_TYPE_CONS: return obj_cons_is_truthy(self);
        case OBJ_TYPE_ERROR: return obj_error_is_truthy(self);
        case OBJ_TYPE_EOF: return obj_eof_is_truthy(self);
        case OBJ_TYPE_NIL: return obj_nil_is_truthy(self);
        case OBJ_TYPE_POINTER: return obj_pointer_is_truthy(self);
        case OBJ_TYPE_BOOL: return obj_bool_is_truthy(self);
        case OBJ_TYPE_VOID: return obj_void_is_truthy(self);
        case OBJ_TYPE_I32: return obj_i32_is_truthy(self);
        case OBJ_TYPE_R64: return obj_r64_is_truthy(self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_is_truthy(self);
        case OBJ_TYPE_STRING: return obj_string_is_truthy(self);
        case OBJ_TYPE_FILE: return obj_file_is_truthy(self);
        case OBJ_TYPE_ENV: return obj_env_is_truthy(self);
        case OBJ_TYPE_ARRAY: return obj_array_is_truthy(self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_is_truthy(self);
        case OBJ_TYPE_FFI: return obj_ffi_is_truthy(self);
        case OBJ_TYPE_MACRO: return obj_macro_is_truthy(self);
        case OBJ_TYPE_CLOSURE: return obj_closure_is_truthy(self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_is_truthy(self);
        case OBJ_TYPE_REPL: return obj_repl_is_truthy(self);
        case OBJ_TYPE_READER: return obj_reader_is_truthy(self);
        default: assert(0);
    }
}

bool obj_is_eq(obj_t* self, obj_t* other) {
    return self == other;
}

size_t obj_hash(obj_t* self) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_hash(self);
        case OBJ_TYPE_CONS: return obj_cons_hash(self);
        case OBJ_TYPE_ERROR: return obj_error_hash(self);
        case OBJ_TYPE_EOF: return obj_eof_hash(self);
        case OBJ_TYPE_NIL: return obj_nil_hash(self);
        case OBJ_TYPE_POINTER: return obj_pointer_hash(self);
        case OBJ_TYPE_BOOL: return obj_bool_hash(self);
        case OBJ_TYPE_VOID: return obj_void_hash(self);
        case OBJ_TYPE_I32: return obj_i32_hash(self);
        case OBJ_TYPE_R64: return obj_r64_hash(self);
        case OBJ_TYPE_SYMBOL: return obj_symbol_hash(self);
        case OBJ_TYPE_STRING: return obj_string_hash(self);
        case OBJ_TYPE_FILE: return obj_file_hash(self);
        case OBJ_TYPE_ENV: return obj_env_hash(self);
        case OBJ_TYPE_ARRAY: return obj_array_hash(self);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_hash(self);
        case OBJ_TYPE_FFI: return obj_ffi_hash(self);
        case OBJ_TYPE_MACRO: return obj_macro_hash(self);
        case OBJ_TYPE_CLOSURE: return obj_closure_hash(self);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_hash(self);
        case OBJ_TYPE_REPL: return obj_repl_hash(self);
        case OBJ_TYPE_READER: return obj_reader_hash(self);
        default: assert(0);
    }
}

obj_t* obj_eval(obj_t* self, obj_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_eval(self, env);
        case OBJ_TYPE_CONS: return obj_cons_eval(self, env);
        case OBJ_TYPE_ERROR: return obj_error_eval(self, env);
        case OBJ_TYPE_EOF: return obj_eof_eval(self, env);
        case OBJ_TYPE_NIL: return obj_nil_eval(self, env);
        case OBJ_TYPE_POINTER: return obj_pointer_eval(self, env);
        case OBJ_TYPE_BOOL: return obj_bool_eval(self, env);
        case OBJ_TYPE_VOID: return obj_void_eval(self, env);
        case OBJ_TYPE_I32: return obj_i32_eval(self, env);
        case OBJ_TYPE_R64: return obj_r64_eval(self, env);
        case OBJ_TYPE_SYMBOL: return obj_symbol_eval(self, env);
        case OBJ_TYPE_STRING: return obj_string_eval(self, env);
        case OBJ_TYPE_FILE: return obj_file_eval(self, env);
        case OBJ_TYPE_ENV: return obj_env_eval(self, env);
        case OBJ_TYPE_ARRAY: return obj_array_eval(self, env);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_eval(self, env);
        case OBJ_TYPE_FFI: return obj_ffi_eval(self, env);
        case OBJ_TYPE_MACRO: return obj_macro_eval(self, env);
        case OBJ_TYPE_CLOSURE: return obj_closure_eval(self, env);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_eval(self, env);
        case OBJ_TYPE_REPL: return obj_repl_eval(self, env);
        case OBJ_TYPE_READER: return obj_reader_eval(self, env);
        default: assert(0);
    }
}

obj_t* obj_apply(obj_t* self, obj_t* args, obj_t* env) {
    switch (self->type) {
        case OBJ_TYPE_LISP_TYPE: return obj_lisp_type_apply(self, args, env);
        case OBJ_TYPE_CONS: return obj_cons_apply(self, args, env);
        case OBJ_TYPE_ERROR: return obj_error_apply(self, args, env);
        case OBJ_TYPE_EOF: return obj_eof_apply(self, args, env);
        case OBJ_TYPE_NIL: return obj_nil_apply(self, args, env);
        case OBJ_TYPE_POINTER: return obj_pointer_apply(self, args, env);
        case OBJ_TYPE_BOOL: return obj_bool_apply(self, args, env);
        case OBJ_TYPE_VOID: return obj_void_apply(self, args, env);
        case OBJ_TYPE_I32: return obj_i32_apply(self, args, env);
        case OBJ_TYPE_R64: return obj_r64_apply(self, args, env);
        case OBJ_TYPE_SYMBOL: return obj_symbol_apply(self, args, env);
        case OBJ_TYPE_STRING: return obj_string_apply(self, args, env);
        case OBJ_TYPE_FILE: return obj_file_apply(self, args, env);
        case OBJ_TYPE_ENV: return obj_env_apply(self, args, env);
        case OBJ_TYPE_ARRAY: return obj_array_apply(self, args, env);
        case OBJ_TYPE_HASH_TABLE: return obj_hash_table_apply(self, args, env);
        case OBJ_TYPE_FFI: return obj_ffi_apply(self, args, env);
        case OBJ_TYPE_MACRO: return obj_macro_apply(self, args, env);
        case OBJ_TYPE_CLOSURE: return obj_closure_apply(self, args, env);
        case OBJ_TYPE_PRIMITIVE: return obj_primitive_apply(self, args, env);
        case OBJ_TYPE_REPL: return obj_repl_apply(self, args, env);
        case OBJ_TYPE_READER: return obj_reader_apply(self, args, env);
        default: assert(0);
    }
}
