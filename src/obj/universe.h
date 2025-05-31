#ifndef UNIVERSE_H
# define UNIVERSE_H

# include <backtrace.h>

# include "obj_lisp_type.h"
# include "obj_combination.h"
# include "obj_error.h"
# include "obj_eof.h"
# include "obj_nil.h"
# include "obj_pointer.h"
# include "obj_bool.h"
# include "obj_void.h"
# include "obj_char.h"
# include "obj_uchar.h"
# include "obj_int.h"
# include "obj_uint.h"
# include "obj_short.h"
# include "obj_ushort.h"
# include "obj_long.h"
# include "obj_ulong.h"
# include "obj_size_t.h"
# include "obj_float.h"
# include "obj_double.h"
# include "obj_symbol.h"
# include "obj_string.h"
# include "obj_file.h"
# include "obj_env.h"
# include "obj_array.h"
# include "obj_hash_table.h"
# include "obj_ffi.h"
# include "obj_macro.h"
# include "obj_closure.h"
# include "obj_primitive.h"
# include "obj_repl.h"
# include "obj_reader.h"

typedef struct universe_t {
    int argc;
    char** argv;
    struct backtrace_state* backtrace_state;
} universe_t;

extern universe_t UNIVERSE;
void universe_init(int argc, char** argv);
void universe_deinit(void);

#endif // UNIVERSE_H
