#ifndef ERR_H
# define ERR_H

# include "memory.h"

void err_init();
void err_destroy();

obj_t* err(const char* format, ...);
obj_t* err_obj(obj_t* obj, const char* format, ...);

#endif // ERR_H
