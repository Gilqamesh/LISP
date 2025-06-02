#include "err.h"

static size_t stack_frames_top = 0;
static size_t stack_frames_size = 0;
static stack_frame_t* stack_frames;

void err_throw(void* context) {
    assert(stack_frames_top && "throw called without matching begin_try");
    --stack_frames_top;
    stack_frames[stack_frames_top].context = context;
    longjmp(stack_frames[stack_frames_top].env, 1);
}

stack_frame_t* err_begin_try() {
    if (!stack_frames) {
        stack_frames_size = 16;
        stack_frames = malloc(stack_frames_size * sizeof(*stack_frames));
    } else if (stack_frames_top == stack_frames_size) {
        stack_frames_size *= 2;
        stack_frames = realloc(stack_frames, stack_frames_size * sizeof(*stack_frames));
    }
    assert(stack_frames_top < stack_frames_size);
    stack_frames[stack_frames_top].context = NULL;
    return &stack_frames[stack_frames_top++];
}

void err_end_try() {
    assert(stack_frames_top && "end_try called without matching begin_try");
    --stack_frames_top;
}

void* err_catch_context() {
    return stack_frames[stack_frames_top].context;
}
