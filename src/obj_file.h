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
obj_t* obj_file_new(const char* path, const char* mode);
obj_t* obj_file_new_from_fp(FILE* borrowed_fp);
void obj_file_delete(obj_t* self);

bool is_file(obj_t* self);
obj_file_t* obj_as_file(obj_t* self);
ffi_type* obj_file_to_ffi(obj_t* self);
void obj_file_to_string(obj_t* self, obj_t* string);
obj_t* obj_file_copy(obj_t* self);
bool obj_file_is_equal(obj_t* self, obj_t* other);
bool obj_file_is_truthy(obj_t* self);
size_t obj_file_hash(obj_t* self);
obj_t* obj_file_eval(obj_t* self, obj_t* env);
obj_t* obj_file_apply(obj_t* self, obj_t* args, obj_t* env);

char obj_file_peek_char(obj_t* self);
char obj_file_read_char(obj_t* self);
void obj_file_unread_char(obj_t* self, char c);
bool obj_file_is_at_end(obj_t* self);

#endif // OBJ_FILE_H
