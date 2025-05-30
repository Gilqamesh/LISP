#ifndef OBJ_FILE_H
# define OBJ_FILE_H

# include "obj.h"

typedef struct obj_file_t {
    obj_t base;
    const char* path;
    FILE* fp;
} obj_file_t;

// using fopen(path, mode)
obj_file_t* obj_file_new(const char* path, const char* mode);
void obj_file_delete(obj_file_t* self);

bool is_file(const obj_t* self);
obj_ffi_t* obj_file_to_ffi(const obj_file_t* self);
void obj_file_to_string(const obj_file_t* self, obj_string_t* str);
obj_t* obj_file_copy(const obj_file_t* self);
bool obj_file_equal(const obj_file_t* self, const obj_file_t* other);
size_t obj_file_hash(const obj_file_t* self);
obj_t* obj_file_eval(const obj_file_t* self, obj_hash_table_t* env);
obj_t* obj_file_apply(const obj_file_t* self, obj_array_t* args, obj_hash_table_t* env);

obj_t* obj_file_read(const obj_file_t* self);
obj_t* obj_file_write(const obj_file_t* self, const obj_t* obj);

#endif // OBJ_FILE_H
