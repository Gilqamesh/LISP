#ifndef OBJ_H
# define OBJ_H

# include "str.h"

typedef enum obj_type_t {
  OBJ_TYPE_ERROR,
  OBJ_TYPE_EOF,
  OBJ_TYPE_NIL,
  OBJ_TYPE_VOID,
  OBJ_TYPE_BOOL,
  OBJ_TYPE_CONS,
  OBJ_TYPE_REAL,
  OBJ_TYPE_SYMBOL,
  OBJ_TYPE_STRING,
  OBJ_TYPE_PRIMITIVE,
  OBJ_TYPE_MACRO,
  OBJ_TYPE_FILE,

  __OBJ_TYPE_SIZE
} obj_type_t;

typedef struct obj_t {
  obj_type_t type;
} obj_t;
void obj_init(obj_t* obj, obj_type_t obj_type);
void obj_to_string(obj_t* obj, str_t* str);
obj_type_t type(obj_t* obj);

typedef struct obj_error_t {
  obj_t base;
  str_t message;
} obj_error_t;
void obj_error_init(obj_error_t* obj_error, str_t message);
void obj_error_to_string(obj_error_t* obj_error, str_t* str);
bool is_error(obj_t* obj);
const str_t* get_error_message(obj_t* obj);

typedef struct obj_eof_t {
  obj_t base;
} obj_eof_t;
void obj_eof_init(obj_eof_t* obj_eof);
void obj_eof_to_string(obj_eof_t* obj_eof, str_t* str);
bool is_eof(obj_t* obj);

typedef struct obj_nil_t {
  obj_t base;
} obj_nil_t;
void obj_nil_init(obj_nil_t* obj_nil);
void obj_nil_to_string(obj_nil_t* obj_nil, str_t* str);
bool is_nil(obj_t* obj);

typedef struct obj_void_t {
  obj_t base;
} obj_void_t;
void obj_void_init(obj_void_t* obj_void);
void obj_void_to_string(obj_void_t* obj_void, str_t* str);
bool is_void(obj_t* obj);

typedef struct obj_bool_t {
  obj_t base;
  bool value;
} obj_bool_t;
void obj_bool_init(obj_bool_t* obj_bool, bool value);
void obj_bool_to_string(obj_bool_t* obj_bool, str_t* str);
bool is_bool(obj_t* obj);
bool get_bool(obj_t* obj);

typedef struct obj_cons_t {
  obj_t base;
  obj_t* car;
  obj_t* cdr;
} obj_cons_t;
void obj_cons_init(obj_cons_t* obj_cons, obj_t* car, obj_t* cdr);
void obj_cons_to_string(obj_cons_t* obj_cons, str_t* str);
bool is_cons(obj_t* obj);
obj_t* get_car(obj_t* obj);
obj_t* get_cdr(obj_t* obj);
void set_car(obj_t* obj, obj_t* car);
void set_cdr(obj_t* obj, obj_t* cdr);

typedef struct obj_real_t {
  obj_t base;
  double real;
} obj_real_t;
void obj_real_init(obj_real_t* obj_real, double real);
void obj_real_to_string(obj_real_t* obj_real, str_t* str);
bool is_real(obj_t* obj);
double get_real(obj_t* obj);

typedef struct obj_symbol_t {
  obj_t base;
  str_t symbol;
} obj_symbol_t;
void obj_symbol_init(obj_symbol_t* obj_symbol, str_t symbol);
void obj_symbol_to_string(obj_symbol_t* obj_symbol, str_t* str);
bool is_symbol(obj_t* obj);
const str_t* get_symbol(obj_t* obj);

typedef struct obj_string_t {
  obj_t base;
  str_t string;
} obj_string_t;
void obj_string_init(obj_string_t* obj_string, str_t string);
void obj_string_to_string(obj_string_t* obj_string, str_t* str);
bool is_string(obj_t* obj);
const str_t* get_string(obj_t* obj);

typedef obj_t* (*primitive_t)(obj_t* self, obj_t* args);
typedef struct obj_primitive_t {
  obj_t base;
  primitive_t primitive;
  str_t name;
} obj_primitive_t;
void obj_primitive_init(obj_primitive_t* obj_primitive, str_t name, primitive_t primitive);
void obj_primitive_to_string(obj_primitive_t* obj_primitive, str_t* str);
bool is_primitive(obj_t* obj);
primitive_t get_primitive(obj_t* obj);
const str_t* get_primitive_name(obj_t* obj);

typedef obj_t* (*macro_t)(obj_t* self, obj_t* args);
typedef struct obj_macro_t {
  obj_t base;
  macro_t macro;
  str_t name;
} obj_macro_t;
void obj_macro_init(obj_macro_t* obj_macro, str_t name, macro_t macro);
void obj_macro_to_string(obj_macro_t* obj_macro, str_t* str);
bool is_macro(obj_t* obj);
macro_t get_macro(obj_t* obj);
const str_t* get_macro_name(obj_t* obj);

typedef struct obj_file_t {
  obj_t base;
  FILE* file;
} obj_file_t;
void obj_file_init(obj_file_t* obj_fd, FILE* file);
void obj_file_to_string(obj_file_t* obj_fd, str_t* str);
bool is_file(obj_t* obj);
FILE* get_file(obj_t* obj);

#endif // OBJ_H
