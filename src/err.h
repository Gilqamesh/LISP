#ifndef ERR_H
# define ERR_H

# include "libc.h"

typedef struct stack_frame_t {
    jmp_buf env;
    void* context;
} stack_frame_t;

void err_throw(void* context);

stack_frame_t* err_begin_try();
void err_end_try();

#define try if (!setjmp(err_begin_try()->env)) {
#define catch err_end_try(); } else

void* err_catch_context();

#endif // ERR_H
