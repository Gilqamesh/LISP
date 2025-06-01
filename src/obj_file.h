#ifndef OBJ_FILE_H
# define OBJ_FILE_H

# include "obj.h"

typedef struct obj_file_t {
    obj_t base;
    char path[256];
    FILE* fp;
    bool owns_fp;
} obj_file_t;

// using fopen(path, mode)
obj_file_t* obj_file_new(const char* path, const char* mode);
obj_file_t* obj_file_new_from_fp(FILE* borrowed_fp);
void obj_file_delete(obj_file_t* self);

bool is_file(const obj_t* self);
obj_ffi_t* obj_file_to_ffi(const obj_file_t* self);
void obj_file_to_string(const obj_file_t* self, obj_string_t* str);
obj_file_t* obj_file_copy(const obj_file_t* self);
bool obj_file_equal(const obj_file_t* self, const obj_file_t* other);
bool obj_file_is_truthy(const obj_file_t* self);
size_t obj_file_hash(const obj_file_t* self);
obj_t* obj_file_eval(const obj_file_t* self, obj_env_t* env);
obj_t* obj_file_apply(const obj_file_t* self, obj_t* args, obj_env_t* env);

char obj_file_peek_char(const obj_file_t* self);
char obj_file_read_char(const obj_file_t* self);
void obj_file_unread_char(const obj_file_t* self, char c);
bool obj_file_is_at_end(const obj_file_t* self);

#endif // OBJ_FILE_H
