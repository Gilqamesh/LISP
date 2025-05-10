#ifndef ERR_H
# define ERR_H

# include "memory.h"
# include "str.h"

void err_init();
void err_destroy();

obj_t* err_null_terminated(str_t message, const char* stringified_params, ...);
// ex. usage: err(memory, obj1, obj2, obj3)
# define err(message, ...) err_null_terminated(message, #__VA_ARGS__, __VA_ARGS__, 0)

#endif // ERR_H
