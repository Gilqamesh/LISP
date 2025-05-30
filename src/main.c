#include "obj_repl.h"
#include "obj_hash_table.h"

int main() {
    obj_hash_table_t* env = obj_hash_table_new();
    try {
        obj_repl_t* repl = obj_repl_new();
        obj_repl_eval(repl, env);
        obj_repl_delete(repl);
    } catch {
        obj_t* err = (obj_t*) err_catch_context();
        str_t str = str_new();
        obj_to_string(err, &str);
        printf("%s\n", str_cstr(&str));
        str_delete(&str);
    }
    obj_hash_table_delete(env);

    return 0;
}
