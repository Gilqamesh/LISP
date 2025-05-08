#ifndef READER_H
# define READER_H

# include "libc.h"
# include "memory.h"

typedef struct reader_t reader_t;

typedef obj_t* (*reader_function_t)(reader_t* self, FILE* file);

typedef struct reader_node_t {
    struct reader_node_t* children[128];
    reader_function_t reader_function;
} reader_node_t;

void reader_node_init(reader_node_t* self);
void reader_node_destroy(reader_node_t* self);

struct reader_t {
    reader_node_t root;
    memory_t* memory;
};

void reader_init(reader_t* self, memory_t* memory);
void reader_destroy(reader_t* self);

void reader_register_reader_macro_str(reader_t* self, const char* name, reader_function_t reader_function);
void reader_register_reader_macro_char(reader_t* self, char c, reader_function_t reader_function);

char reader_peek(reader_t* self, FILE* file);
char reader_get_char(reader_t* self, FILE* file);
void reader_unget_char(reader_t* self, FILE* file, char c);
bool reader_is_at_end(reader_t* self, FILE* file);
bool reader_is_whitespace(reader_t* self, char c);

obj_t* reader_read(reader_t* self, FILE* file);

#endif // READER_H
