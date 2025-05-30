#include "universe.h"

int main(int argc, char** argv) {
    universe_init(argc, argv);

    obj_hash_table_t* env = obj_hash_table_new();
    try {
        obj_repl_t* repl = obj_repl_new();
        obj_repl_eval(repl, env);
        obj_repl_delete(repl);
    } catch {
        obj_t* err = (obj_t*) err_catch_context();
        obj_string_t* str = obj_string_new();
        obj_to_string(err, str);
        printf("%s\n", obj_string_cstr(str));
        obj_string_delete(str);
    }
    obj_hash_table_delete(env);

    universe_destroy();

    return 0;
}
