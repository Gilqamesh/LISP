#ifndef OBJ_READER_H
# define OBJ_READER_H

# include "obj.h"

typedef obj_t* (*reader_fn_t)(obj_t* self, obj_t* lexeme);

typedef struct reader_node_t {
    struct reader_node_t* children[128];
    reader_fn_t reader_fn;
} reader_node_t;

struct obj_reader_t {
    obj_t base;
    obj_t* file;
    reader_node_t reader_node;
    reader_fn_t default_reader_fn;
    bool is_top_level;
};

obj_t* obj_reader_new(obj_t* file, reader_fn_t default_reader_fn);
void obj_reader_delete(obj_t* self);

bool is_reader(obj_t* self);
obj_reader_t* obj_as_reader(obj_t* self);
ffi_type* obj_reader_to_ffi(obj_t* self);
void obj_reader_to_string(obj_t* self, obj_t* string);
obj_t* obj_reader_copy(obj_t* self);
bool obj_reader_is_equal(obj_t* self, obj_t* other);
bool obj_reader_is_truthy(obj_t* self);
size_t obj_reader_hash(obj_t* self);
obj_t* obj_reader_eval(obj_t* self, obj_t* env);
obj_t* obj_reader_apply(obj_t* self, obj_t* args, obj_t* env);

obj_t* obj_reader_add_reader_function(obj_t* self, const char* prefix, reader_fn_t reader_fn);
obj_t* obj_reader_add_reader_function_char(obj_t* self, char c, reader_fn_t reader_fn);
obj_t* obj_reader_read(obj_t* self);

obj_t* obj_reader_default_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_skip_whitespaces_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_left_paren_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_right_paren_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_double_quote_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_quote_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_backtick_reader(obj_t* self, obj_t* lexeme);
obj_t* obj_reader_comma_reader(obj_t* self, obj_t* lexeme);

#endif // OBJ_READER_H
