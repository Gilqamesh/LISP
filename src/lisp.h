#ifndef LISP_H
# define LISP_H

# include "memory.h"

obj_t* eval(memory_t* memory, obj_t* obj, obj_t* env);
obj_t* apply(memory_t* memory, obj_t* op, obj_t* args, obj_t* env);
obj_t* macroexpand(memory_t* memory, obj_t* op, obj_t* env);
obj_t* macroexpand_1(memory_t* memory, obj_t* op, obj_t* env);
void print(memory_t* memory, obj_t* obj, FILE* file);

obj_t* list_null_terminated(memory_t* self, ...);
// ex. usage: list(memory, obj1, obj2, obj3)
# define list(memory, ...) list_null_terminated(memory, __VA_ARGS__, 0)

bool is_list(obj_t* obj);
size_t list_length(obj_t* obj);
obj_t* list_tail(obj_t* list, size_t index);
obj_t* list_ref(obj_t* list, size_t index);

bool is_eq(obj_t* obj1, obj_t* obj2);
bool is_true(obj_t* obj);
bool is_false(obj_t* obj);

obj_t* begin(memory_t* memory, obj_t* obj, obj_t* env);

obj_t* list_of_values(memory_t* memory, obj_t* args, obj_t* env);

obj_t* env_extend(memory_t* memory, obj_t* env, obj_t* params, obj_t* args);

void obj_to_string(const obj_t* obj, str_t* str);

#endif // LISP_H
