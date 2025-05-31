#ifndef OBJ_READER_H
# define OBJ_READER_H

# include "obj.h"

typedef obj_t* (*reader_fn_t)(obj_reader_t* self);

typedef struct reader_node_t {
    struct reader_node_t* children[128];
    reader_fn_t reader_fn;
} reader_node_t;

struct obj_reader_t {
    obj_t base;
    obj_file_t* file;
    reader_node_t reader_node;
    reader_fn_t default_reader_fn;
    obj_string_t* lexeme;
};

obj_reader_t* obj_reader_new(obj_file_t* file, reader_fn_t default_reader_fn);
void obj_reader_delete(obj_reader_t* self);

bool is_reader(const obj_t* self);
obj_ffi_t* obj_reader_to_ffi(const obj_reader_t* self);
void obj_reader_to_string(const obj_reader_t* self, obj_string_t* other);
obj_reader_t* obj_reader_copy(const obj_reader_t* self);
bool obj_reader_equal(const obj_reader_t* self, const obj_reader_t* other);
size_t obj_reader_hash(const obj_reader_t* self);
obj_t* obj_reader_eval(const obj_reader_t* self, obj_env_t* env);
obj_t* obj_reader_apply(const obj_reader_t* self, obj_array_t* args, obj_env_t* env);

obj_t* obj_reader_add_reader_function(obj_reader_t* self, const char* prefix, reader_fn_t reader_fn);
obj_t* obj_reader_read(obj_reader_t* self);

#endif // OBJ_READER_H
