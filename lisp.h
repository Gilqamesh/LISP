#ifndef LISP_H
# define LISP_H

# include "memory.h"

obj_t* list_null_terminated(memory_t* self, ...);
# define list(memory, ...) list_null_terminated(memory, __VA_ARGS__, NULL)

bool is_list(obj_t* obj);
size_t list_length(obj_t* obj);
obj_t* list_tail(obj_t* list, size_t index);
obj_t* list_ref(obj_t* list, size_t index);

bool is_eq(obj_t* obj1, obj_t* obj2);

#endif // LISP_H
