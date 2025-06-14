#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

typedef struct type_t {
    char name[256];
    struct type_t* next;
} type_t;

FILE* fp_type_names = 0;
FILE* fp_obj_h = 0;
FILE* fp_obj_c = 0;
FILE* fp_universe_h = 0;
FILE* fp_universe_c = 0;

void exit_clean(const char* format, ...) {
    if (fp_type_names) {
        fclose(fp_type_names);
        fp_type_names = 0;
    }
    if (fp_obj_h) {
        fclose(fp_obj_h);
        fp_obj_h = 0;
    }
    if (fp_obj_c) {
        fclose(fp_obj_c);
        fp_obj_c = 0;
    }
    if (fp_universe_h) {
        fclose(fp_universe_h);
        fp_universe_h = 0;
    }
    if (fp_universe_c) {
        fclose(fp_universe_c);
        fp_universe_c = 0;
    }
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    exit(0);
}

int main(int argc, char** argv ) {
    if (argc != 3) {
        exit_clean("Usage: %s <type-names.txt> <output-dir>\n", argv[0]);
    }
    const char* obj_types_path = argv[1];
    const char* output_dir = argv[2];

    fp_type_names = fopen(obj_types_path, "r");
    if (!fp_type_names) {
        exit_clean("Error: Could not open %s\n", obj_types_path);
    }

    char obj_h_base[256] = "obj.h";
    char obj_h_path[256];
    snprintf(obj_h_path, sizeof(obj_h_path), "%s/%s", output_dir, obj_h_base);
    fp_obj_h = fopen(obj_h_path, "w");
    if (!fp_obj_h) {
        exit_clean("Error: Could not create %s\n", obj_h_path);
    }

    char obj_c_base[256] = "obj.c";
    char obj_c_path[256];
    snprintf(obj_c_path, sizeof(obj_c_path), "%s/%s", output_dir, obj_c_base);
    fp_obj_c = fopen(obj_c_path, "w");
    if (!fp_obj_c) {
        exit_clean("Error: Could not create %s\n", obj_c_path);
    }

    char obj_universe_h_base[256] = "universe.h";
    char obj_universe_h_path[256];
    snprintf(obj_universe_h_path, sizeof(obj_universe_h_path), "%s/%s", output_dir, obj_universe_h_base);
    fp_universe_h = fopen(obj_universe_h_path, "w");
    if (!fp_universe_h) {
        exit_clean("Error: Could not create universe.h\n");
    }

    char obj_universe_c_base[256] = "universe.c";
    char obj_universe_c_path[256];
    snprintf(obj_universe_c_path, sizeof(obj_universe_c_path), "%s/%s", output_dir, obj_universe_c_base);
    fp_universe_c = fopen(obj_universe_c_path, "w");
    if (!fp_universe_c) {
        exit_clean("Error: Could not create universe.c\n");
    }

    fprintf(fp_universe_h, "#ifndef UNIVERSE_H\n");
    fprintf(fp_universe_h, "# define UNIVERSE_H\n");
    fprintf(fp_universe_h, "\n");

    type_t* type_head = NULL;
    type_t** type_tail = &type_head;

    while (fp_type_names) {
        char type_name[256];
        if (fscanf(fp_type_names, "%255s", type_name) == EOF) {
            break ;
        }
        printf("Processing type: %s\n", type_name);
        char type_name_upper[256];
        int i = 0;
        while (type_name[i]) {
            type_name_upper[i] = toupper(type_name[i]);
            ++i;
        }
        type_name_upper[i] = '\0';

        *type_tail = malloc(sizeof(**type_tail));
        snprintf((*type_tail)->name, sizeof((*type_tail)->name), "%s", type_name);
        (*type_tail)->next = NULL;
        type_tail = &(*type_tail)->next;

        char header_base[256];
        snprintf(header_base, sizeof(header_base), "obj_%s.h", type_name);
        char header_path[256];
        char source_base[256];
        snprintf(source_base, sizeof(source_base), "obj_%s.c", type_name);
        char source_path[256];
        snprintf(header_path, sizeof(header_path), "%s/%s", output_dir, header_base);
        snprintf(source_path, sizeof(source_path), "%s/%s", output_dir, source_base);

        fprintf(fp_universe_h, "# include \"%s\"\n", header_base);

        FILE* fp = fopen(header_path, "r");
        if (!fp) {
            fp = fopen(header_path, "w");
            if (!fp) {
                fclose(fp);
                exit_clean("Error: Could not create %s\n", header_path);
            }
            fprintf(fp, "#ifndef OBJ_%s_H\n", type_name_upper);
            fprintf(fp, "# define OBJ_%s_H\n", type_name_upper);
            fprintf(fp, "\n");
            fprintf(fp, "# include \"%s\"\n", obj_h_base);
            fprintf(fp, "\n");
            fprintf(fp, "struct obj_%s_t {\n", type_name);
            fprintf(fp, "    obj_t base;\n");
            fprintf(fp, "};\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_new();\n", type_name);
            fprintf(fp, "void obj_%s_delete(obj_t* self);\n", type_name);
            fprintf(fp, "\n");
            fprintf(fp, "bool is_%s(obj_t* self);\n", type_name);
            fprintf(fp, "obj_%s_t* obj_as_%s(obj_t* self);", type_name, type_name);
            fprintf(fp, "ffi_type* obj_%s_to_ffi(obj_t* self);\n", type_name);
            fprintf(fp, "obj_t* obj_%s_to_string(obj_t* self, obj_t* string);\n", type_name);
            fprintf(fp, "obj_t* obj_%s_copy(obj_t* self);\n", type_name);
            fprintf(fp, "bool obj_%s_is_equal(obj_t* self, obj_t* other);\n", type_name);
            fprintf(fp, "bool obj_%s_is_truthy(obj_t* self);\n", type_name);
            fprintf(fp, "size_t obj_%s_hash(obj_t* self);\n", type_name);
            fprintf(fp, "obj_t* obj_%s_eval(obj_t* self, obj_t* env);\n", type_name);
            fprintf(fp, "obj_t* obj_%s_apply(obj_t* self, obj_t* args, obj_t* env);\n", type_name);
            fprintf(fp, "\n");
            fprintf(fp, "#endif // OBJ_%s_H\n", type_name_upper);
            fclose(fp);
        }
        fp = fopen(source_path, "r");
        if (!fp) {
            fp = fopen(source_path, "w");
            if (!fp) {
                exit_clean("Error: Could not create %s\n", source_path);
            }
            fprintf(fp, "#include \"%s\"\n", obj_universe_h_base);
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_new() {\n", type_name);
            fprintf(fp, "    obj_%s_t* self = (obj_%s_t*) malloc(sizeof(obj_%s_t));\n", type_name, type_name, type_name);
            fprintf(fp, "    obj_init((obj_t*) self, OBJ_TYPE_%s);\n", type_name_upper);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    return (obj_t*) self;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "void obj_%s_delete(obj_t* self) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    free(self);\n");
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "bool is_%s(obj_t* self) {\n", type_name);
            fprintf(fp, "    return obj_get_type(self) == OBJ_TYPE_%s;\n", type_name_upper);
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_%s_t* obj_as_%s(obj_t* self) {\n", type_name, type_name);
            fprintf(fp, "    if (!is_%s(self)) {\n", type_name);
            fprintf(fp, "        throw(obj_string_new_cstr(\"expected %%s, got %%s\", \"obj_%s\", obj_type_to_string(obj_get_type(self))), self);\n", type_name);
            fprintf(fp, "    }\n");
            fprintf(fp, "    return (obj_%s_t*) self;\n", type_name);
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "ffi_type* obj_%s_to_ffi(obj_t* self) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "void obj_%s_to_string(obj_t* self, obj_t* string) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    obj_string_push_cstr(string, \"<%%s \", obj_type_to_string(obj_get_type(self)));\n");
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    obj_string_push_cstr(string, \">\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_copy(obj_t* self) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    obj_t* copy = obj_%s_new();\n", type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    return copy;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "bool obj_%s_is_equal(obj_t* self, obj_t* other) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s_self = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    obj_%s_t* obj_%s_other = obj_as_%s(other);\n", type_name, type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "bool obj_%s_is_truthy(obj_t* self) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "size_t obj_%s_hash(obj_t* self) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_eval(obj_t* self, obj_t* env) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    return self;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_apply(obj_t* self, obj_t* args, obj_t* env) {\n", type_name);
            fprintf(fp, "    obj_%s_t* obj_%s = obj_as_%s(self);\n", type_name, type_name, type_name);
            fprintf(fp, "    throw(obj_string_new_cstr(\"cannot apply %%s\", obj_type_to_string(obj_get_type(self))), self);\n");
            fprintf(fp, "}\n");
            fclose(fp);
        }
    }

    fprintf(fp_universe_h, "\n");
    fprintf(fp_universe_h, "typedef struct universe_t {\n");
    fprintf(fp_universe_h, "    int argc;\n");
    fprintf(fp_universe_h, "    char** argv;\n");
    fprintf(fp_universe_h, "    struct backtrace_state* backtrace_state;\n");
    fprintf(fp_universe_h, "} universe_t;\n");
    fprintf(fp_universe_h, "\n");
    fprintf(fp_universe_h, "extern universe_t UNIVERSE;\n");
    fprintf(fp_universe_h, "void universe_init(int argc, char** argv);\n");
    fprintf(fp_universe_h, "void universe_deinit(void);\n");
    fprintf(fp_universe_h, "\n");
    fprintf(fp_universe_h, "#endif // UNIVERSE_H\n");

    fprintf(fp_universe_c, "#include \"universe.h\"\n");
    fprintf(fp_universe_c, "\n");
    fprintf(fp_universe_c, "universe_t UNIVERSE;\n");
    fprintf(fp_universe_c, "\n");
    fprintf(fp_universe_c, "void universe_init(int argc, char** argv) {\n");
    fprintf(fp_universe_c, "    UNIVERSE.argc = argc;\n");
    fprintf(fp_universe_c, "    UNIVERSE.argv = argv;\n");
    fprintf(fp_universe_c, "    UNIVERSE.backtrace_state = backtrace_create_state(argv[0], 0, NULL, NULL);\n");
    fprintf(fp_universe_c, "}\n");
    fprintf(fp_universe_c, "\n");
    fprintf(fp_universe_c, "void universe_deinit(void) {\n");
    fprintf(fp_universe_c, "}\n");

    fprintf(fp_obj_h, "#ifndef OBJ_H\n");
    fprintf(fp_obj_h, "# define OBJ_H\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "# include \"libc.h\"\n");
    // todo: port these to obj types
    fprintf(fp_obj_h, "# include \"err.h\"\n");
    fprintf(fp_obj_h, "# include \"utils.h\"\n");
    fprintf(fp_obj_h, "\n");

    type_t* type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_h, "typedef struct obj_%s_t obj_%s_t;\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }

    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "typedef enum obj_type_t {\n");
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_h, "    OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; ++i) {
            fputc(toupper(type_cur->name[i]), fp_obj_h);
        }
        fprintf(fp_obj_h, ",\n");
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_h, "    _OBJ_TYPE_SIZE\n");
    fprintf(fp_obj_h, "} obj_type_t;\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "const char* obj_type_to_string(obj_type_t type);\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "typedef struct obj_t {\n");
    fprintf(fp_obj_h, "    obj_type_t type;\n");
    fprintf(fp_obj_h, "} obj_t;\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h,  "void obj_init(obj_t* self, obj_type_t type);\n");
    fprintf(fp_obj_h,  "void obj_delete(obj_t* self);\n");
    fprintf(fp_obj_h, "obj_type_t obj_get_type(obj_t* self);\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "void obj_to_string(obj_t* self, obj_t* string);\n");
    fprintf(fp_obj_h, "ffi_type* obj_to_ffi(obj_t* self);\n");
    fprintf(fp_obj_h, "obj_t* obj_copy(obj_t* self);\n");
    fprintf(fp_obj_h, "bool obj_is_equal(obj_t* self, obj_t* other);\n");
    fprintf(fp_obj_h, "bool obj_is_truthy(obj_t* self);\n");
    fprintf(fp_obj_h, "bool obj_is_eq(obj_t* self, obj_t* other);\n");
    fprintf(fp_obj_h, "size_t obj_hash(obj_t* self);\n");
    fprintf(fp_obj_h, "obj_t* obj_eval(obj_t* self, obj_t* env);\n");
    fprintf(fp_obj_h, "obj_t* obj_apply(obj_t* self, obj_t* args, obj_t* env);\n");
    fprintf(fp_obj_h, "\n");
    fprintf(fp_obj_h, "#endif // OBJ_H\n");

    fprintf(fp_obj_c, "#include \"obj.h\"\n");
    fprintf(fp_obj_c, "\n");
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "#include \"obj_%s.h\"\n", type_cur->name);
        type_cur = type_cur->next;
    }

    fprintf(fp_obj_c,
        "\n"
        "const char* obj_type_to_string(obj_type_t type) {\n"
        "    switch (type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return \"%s\";\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "void obj_init(obj_t* self, obj_type_t type) {\n"
        "    self->type = type;\n"
        "}\n"
        "\n"
    );

    fprintf(fp_obj_c,
        "void obj_delete(obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": obj_%s_delete(self); break;\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_type_t obj_get_type(obj_t* self) {\n"
        "    return self->type;\n"
        "}\n"
        "\n"
        "void obj_to_string(obj_t* self, obj_t* string) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": obj_%s_to_string(self, string); break;\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "ffi_type* obj_to_ffi(obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_to_ffi(self);\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_copy(obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_copy(self);\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "bool obj_is_equal(obj_t* self, obj_t* other) {\n"
        "    if (self->type != other->type) {\n"
        "        return false;\n"
        "    }\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_is_equal(self, other);\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "bool obj_is_truthy(obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_is_truthy(self);\n", type_cur->name);
        type_cur = type_cur->next;
    }

    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "bool obj_is_eq(obj_t* self, obj_t* other) {\n"
        "    return self == other;\n"
        "}\n"
        "\n"
        "size_t obj_hash(obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_hash(self);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_eval(obj_t* self, obj_t* env) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_eval(self, env);\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_apply(obj_t* self, obj_t* args, obj_t* env) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_apply(self, args, env);\n", type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
    );

    exit_clean("Code generation completed successfully.\n");
}
