#include "obj.h"

void obj_init(obj_t* obj, obj_type_t obj_type) {
  obj->type = obj_type;
}

void obj_to_string(obj_t* obj, str_t* str) {
  switch (obj->type) {
  case OBJ_TYPE_ERROR: {
    obj_error_to_string((obj_error_t*)obj, str);
  } break ;
  case OBJ_TYPE_EOF: {
    obj_eof_to_string((obj_eof_t*)obj, str);
  } break ;
  case OBJ_TYPE_NIL: {
    obj_nil_to_string((obj_nil_t*)obj, str);
  } break ;
  case OBJ_TYPE_VOID: {
    obj_void_to_string((obj_void_t*)obj, str);
  } break ;
  case OBJ_TYPE_CONS: {
    obj_cons_to_string((obj_cons_t*)obj, str);
  } break ;
  case OBJ_TYPE_REAL: {
    obj_real_to_string((obj_real_t*)obj, str);
  } break ;
  case OBJ_TYPE_SYMBOL: {
    obj_symbol_to_string((obj_symbol_t*)obj, str);
  } break ;
  case OBJ_TYPE_STRING: {
    obj_string_to_string((obj_string_t*)obj, str);
  } break ;
  case OBJ_TYPE_PRIMITIVE: {
    obj_primitive_to_string((obj_primitive_t*)obj, str);
  } break ;
  case OBJ_TYPE_MACRO: {
    obj_macro_to_string((obj_macro_t*)obj, str);
  } break ;
  default: assert(0);
  }
}

obj_type_t type(obj_t* obj) {
  return obj->type;
}

void obj_error_init(obj_error_t* obj_error, str_t message) {
  obj_init(&obj_error->base, OBJ_TYPE_ERROR);
  obj_error->message = message;
}

void obj_error_to_string(obj_error_t* obj_error, str_t* str) {
  str_push(str, "#<error ");
  str_push_str(str, &obj_error->message);
  str_push(str, ">");
}

bool is_error(obj_t* obj) {
  return type(obj) == OBJ_TYPE_ERROR;
}

const str_t* get_error_message(obj_t* obj) {
  assert(is_error(obj));
  return &((obj_error_t*)obj)->message;
}

void obj_eof_init(obj_eof_t* obj_eof) {
  obj_init(&obj_eof->base, OBJ_TYPE_EOF);
}

void obj_eof_to_string(obj_eof_t* obj_eof, str_t* str) {
  str_push(str, "#<eof>");
}

bool is_eof(obj_t* obj) {
  return type(obj) == OBJ_TYPE_EOF;
}

void obj_nil_init(obj_nil_t* obj_nil) {
  obj_init(&obj_nil->base, OBJ_TYPE_NIL);
}

void obj_nil_to_string(obj_nil_t* obj_nil, str_t* str) {
  str_push(str, "#<nil>");
}

bool is_nil(obj_t* obj) {
  return type(obj) == OBJ_TYPE_NIL;
}

void obj_void_init(obj_void_t* obj_void) {
  obj_init(&obj_void->base, OBJ_TYPE_VOID);
}

void obj_void_to_string(obj_void_t* obj_void, str_t* str) {
  str_push(str, "#<void>");
}

bool is_void(obj_t* obj) {
  return type(obj) == OBJ_TYPE_VOID;
}

void obj_bool_init(obj_bool_t* obj_bool, bool value) {
  obj_init(&obj_bool->base, OBJ_TYPE_BOOL);
  obj_bool->value = value;
}

void obj_bool_to_string(obj_bool_t* obj_bool, str_t* str) {
  str_push(str, obj_bool->value ? "#t" : "#f");
}

bool is_bool(obj_t* obj) {
  return type(obj) == OBJ_TYPE_BOOL;
}

bool get_bool(obj_t* obj) {
  assert(is_bool(obj));
  return ((obj_bool_t*)obj)->value;
}

void obj_cons_init(obj_cons_t* obj_cons, obj_t* car, obj_t* cdr) {
  obj_init(&obj_cons->base, OBJ_TYPE_CONS);
  obj_cons->car = car;
  obj_cons->cdr = cdr;
}

void obj_cons_to_string(obj_cons_t* obj_cons, str_t* str) {
  str_push(str, "(");
  obj_t* cur = (obj_t*)obj_cons;
  while (is_cons(cur)) {
    obj_to_string(get_car(cur), str);
    if (is_cons(get_cdr(cur))) {
      str_push(str, " ");
      cur = get_cdr(cur);
    } else if (is_nil(get_cdr(cur))) {
      break ;
    } else {
      str_push(str, " . ");
      obj_to_string(get_cdr(cur), str);
      break ;
    }
  }
  str_push(str, ")");
}

bool is_cons(obj_t* obj) {
  return type(obj) == OBJ_TYPE_CONS;
}

obj_t* get_car(obj_t* obj) {
  assert(is_cons(obj));
  return ((obj_cons_t*)obj)->car;
}

obj_t* get_cdr(obj_t* obj) {
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

void obj_real_to_string(obj_real_t* obj_real, str_t* str) {
  str_push(str, "%f", obj_real->real);
}

bool is_real(obj_t* obj) {
  return type(obj) == OBJ_TYPE_REAL;
}

double get_real(obj_t* obj) {
  assert(is_real(obj));
  return ((obj_real_t*)obj)->real;
}

void obj_symbol_init(obj_symbol_t* obj_symbol, str_t symbol) {
  obj_init(&obj_symbol->base, OBJ_TYPE_SYMBOL);
  obj_symbol->symbol = symbol;
}

void obj_symbol_to_string(obj_symbol_t* obj_symbol, str_t* str) {
  str_push_str(str, &obj_symbol->symbol);
}

bool is_symbol(obj_t* obj) {
  return type(obj) == OBJ_TYPE_SYMBOL;
}

const str_t* get_symbol(obj_t* obj) {
  assert(is_symbol(obj));
  return &((obj_symbol_t*)obj)->symbol;
}

void obj_string_init(obj_string_t* obj_string, str_t string) {
  obj_init(&obj_string->base, OBJ_TYPE_STRING);
  obj_string->string = string;
}

void obj_string_to_string(obj_string_t* obj_string, str_t* str) {
  str_push(str, "\"");
  str_push_str(str, &obj_string->string);
  str_push(str, "\"");
}

bool is_string(obj_t* obj) {
  return type(obj) == OBJ_TYPE_STRING;
}

const str_t* get_string(obj_t* obj) {
  assert(is_string(obj));
  return &((obj_string_t*)obj)->string;
}

void obj_primitive_init(obj_primitive_t* obj_primitive, str_t name, primitive_t primitive) {
  obj_init(&obj_primitive->base, OBJ_TYPE_PRIMITIVE);
  obj_primitive->primitive = primitive;
  obj_primitive->name = name;
}

void obj_primitive_to_string(obj_primitive_t* obj_primitive, str_t* str) {
  str_push(str, "#<primitive ");
  str_push_str(str, &obj_primitive->name);
  str_push(str, ">");
}

bool is_primitive(obj_t* obj) {
  return type(obj) == OBJ_TYPE_PRIMITIVE;
}

primitive_t get_primitive(obj_t* obj) {
  assert(is_primitive(obj));
  return ((obj_primitive_t*)obj)->primitive;
}

const str_t* get_primitive_name(obj_t* obj) {
  assert(is_primitive(obj));
  return &((obj_primitive_t*)obj)->name;
}

void obj_macro_init(obj_macro_t* obj_macro, str_t name, macro_t macro) {
  obj_init(&obj_macro->base, OBJ_TYPE_MACRO);
  obj_macro->macro = macro;
  obj_macro->name = name;
}

void obj_macro_to_string(obj_macro_t* obj_macro, str_t* str) {
  str_push(str, "#<macro ");
  str_push_str(str, &obj_macro->name);
  str_push(str, ">");
}

bool is_macro(obj_t* obj) {
  return type(obj) == OBJ_TYPE_MACRO;
}

macro_t get_macro(obj_t* obj) {
  assert(is_macro(obj));
  return ((obj_macro_t*)obj)->macro;
}

const str_t* get_macro_name(obj_t* obj) {
  assert(is_macro(obj));
  return &((obj_macro_t*)obj)->name;
}

void obj_file_init(obj_file_t* obj_file, FILE* file) {
  obj_init(&obj_file->base, OBJ_TYPE_FILE);
  obj_file->file = file;
}

void obj_file_to_string(obj_file_t* obj_file, str_t* str) {
  str_push(str, "#<file>");
}

bool is_file(obj_t* obj) {
  return type(obj) == OBJ_TYPE_FILE;
}

FILE* get_file(obj_t* obj) {
  assert(is_file(obj));
  return ((obj_file_t*)obj)->file;
}
