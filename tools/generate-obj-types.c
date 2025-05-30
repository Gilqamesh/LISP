#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct type_t {
    char name[256];
    struct type_t* next;
} type_t;

int main(int argc, char** argv ) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <type-names.txt> <output-dir>\n", argv[0]);
        return 1;
    }
    const char* obj_types_path = argv[1];
    const char* output_dir = argv[2];

    FILE* fp_type_names = fopen(obj_types_path, "r");
    if (!fp_type_names) {
        fprintf(stderr, "Error: Could not open %s\n", obj_types_path);
        return 1;
    }

    char obj_h[256];
    snprintf(obj_h, sizeof(obj_h), "%s/obj.h", output_dir);
    FILE* fp_obj_h = fopen(obj_h, "w");
    if (!fp_obj_h) {
        fprintf(stderr, "Error: Could not create %s\n", obj_h);
        fclose(fp_type_names);
        return 1;
    }
    char obj_c[256];
    snprintf(obj_c, sizeof(obj_c), "%s/obj.c", output_dir);
    FILE* fp_obj_c = fopen(obj_c, "w");
    if (!fp_obj_c) {
        fprintf(stderr, "Error: Could not create %s\n", obj_c);
        fclose(fp_type_names);
        fclose(fp_obj_h);
        return 1;
    }

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

        char header[256];
        char source[256];
        snprintf(header, sizeof(header), "%s/obj_%s.h", output_dir, type_name);
        snprintf(source, sizeof(source), "%s/obj_%s.c", output_dir, type_name);
        FILE* fp = fopen(header, "r");
        if (!fp) {
            fp = fopen(header, "w");
            if (!fp) {
                fprintf(stderr, "Error: Could not create %s\n", header);
                fclose(fp_type_names);
                fclose(fp_obj_h);
                fclose(fp_obj_c);
                return 1;
            }
            fprintf(fp, "#ifndef OBJ_%s_H\n", type_name_upper);
            fprintf(fp, "# define OBJ_%s_H\n", type_name_upper);
            fprintf(fp, "\n");
            fprintf(fp, "# include \"obj.h\"\n");
            fprintf(fp, "\n");
            fprintf(fp, "typedef struct obj_%s_t {\n", type_name);
            fprintf(fp, "    obj_t base;\n");
            fprintf(fp, "} obj_%s_t;\n", type_name);
            fprintf(fp, "\n");
            fprintf(fp, "obj_%s_t* obj_%s_new();\n", type_name, type_name);
            fprintf(fp, "void obj_%s_delete(obj_%s_t* self);\n", type_name, type_name);
            fprintf(fp, "\n");
            fprintf(fp, "bool is_%s(const obj_t* self);\n", type_name);
            fprintf(fp, "ffi_type* obj_%s_to_ffi_type(const obj_%s_t* self);\n", type_name, type_name);
            fprintf(fp, "void obj_%s_to_string(const obj_%s_t* self, str_t* str);\n", type_name, type_name);
            fprintf(fp, "obj_t* obj_%s_copy(const obj_%s_t* self);\n", type_name, type_name);
            fprintf(fp, "bool obj_%s_equal(const obj_%s_t* self, const obj_%s_t* other);\n", type_name, type_name, type_name);
            fprintf(fp, "size_t obj_%s_hash(const obj_%s_t* self);\n", type_name, type_name);
            fprintf(fp, "obj_t* obj_%s_eval(const obj_%s_t* self, obj_hash_table_t* env);\n", type_name, type_name);
            fprintf(fp, "obj_t* obj_%s_apply(const obj_%s_t* self, obj_array_t* args, obj_hash_table_t* env);\n", type_name, type_name);
            fprintf(fp, "\n");
            fprintf(fp, "#endif // OBJ_%s_H\n", type_name_upper);
            fclose(fp);
        }
        fp = fopen(source, "r");
        if (!fp) {
            fp = fopen(source, "w");
            if (!fp) {
                fprintf(stderr, "Error: Could not create %s\n", source);
                fclose(fp_type_names);
                fclose(fp_obj_h);
                fclose(fp_obj_c);
                return 1;
            }
            fprintf(fp, "#include \"obj_%s.h\"\n", type_name);
            fprintf(fp, "\n");
            fprintf(fp, "obj_%s_t* obj_%s_new() {\n", type_name, type_name);
            fprintf(fp, "    obj_%s_t* self = (obj_%s_t*) malloc(sizeof(obj_%s_t));\n", type_name, type_name, type_name);
            fprintf(fp, "    obj_init((obj_t*) self, OBJ_TYPE_%s);\n", type_name_upper);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    return self;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "void obj_%s_delete(obj_%s_t* self) {\n", type_name, type_name);
            fprintf(fp, "    free(self);\n");
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "bool is_%s(const obj_t* self) {\n", type_name);
            fprintf(fp, "    return self->type == OBJ_TYPE_%s;\n", type_name_upper);
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "ffi_type* obj_%s_to_ffi_type(const obj_%s_t* self) {\n", type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "void obj_%s_to_string(const obj_%s_t* self, str_t* str) {\n", type_name, type_name);
            fprintf(fp, "    str_push_cstr(str, \"<%s \", obj_type_to_string(obj_get_type((obj_t*) self)));\n", type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    str_push_cstr(str, \">\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_copy(const obj_%s_t* self) {\n", type_name, type_name);
            fprintf(fp, "    obj_%s_t* copy = obj_%s_new();\n", type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "    return (obj_t*) copy;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "bool obj_%s_equal(const obj_%s_t* self, const obj_%s_t* other) {\n", type_name, type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "size_t obj_%s_hash(const obj_%s_t* self) {\n", type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_eval(const obj_%s_t* self, obj_hash_table_t* env) {\n", type_name, type_name);
            fprintf(fp, "    return (obj_t*) self;\n");
            fprintf(fp, "}\n");
            fprintf(fp, "\n");
            fprintf(fp, "obj_t* obj_%s_apply(const obj_%s_t* self, obj_array_t* args, obj_hash_table_t* env) {\n", type_name, type_name);
            fprintf(fp, "    assert(0 && \"todo: implement\");\n");
            fprintf(fp, "}\n");
            fclose(fp);
        }
    }

    fprintf(fp_obj_h,
        "#ifndef OBJ_H\n"
        "# define OBJ_H\n"
        "\n"
        "# include \"libc.h\"\n"
        "# include \"str.h\"\n"
        "# include \"darr.h\"\n"
        "# include \"hash_table.h\"\n"
        "# include \"err.h\"\n"
        "# include \"ffi.h\"\n"
        "\n"
    );

    // forward declarations
    type_t* type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_h, "typedef struct obj_%s_t obj_%s_t;\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }

    fprintf(fp_obj_h,
        "\n"
        "typedef enum obj_type_t {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_h, "    OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; ++i) {
            fputc(toupper(type_cur->name[i]), fp_obj_h);
        }
        fprintf(fp_obj_h, ",\n");
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_h,
        "    _OBJ_TYPE_SIZE\n"
        "} obj_type_t;\n"
        "\n"
        "const char* obj_type_to_string(obj_type_t type);\n"
        "\n"
        "typedef struct obj_t {\n"
        "    obj_type_t type;\n"
        "} obj_t;\n"
        "void obj_init(obj_t* self, obj_type_t type);\n"
        "obj_type_t obj_get_type(const obj_t* self);\n"
        "\n"
        "void obj_to_string(const obj_t* self, str_t* str);\n"
        "ffi_type* obj_to_ffi_type(const obj_t* self);\n"
        "obj_t* obj_copy(const obj_t* self);\n"
        "bool obj_equal(const obj_t* self, const obj_t* other);\n"
        "size_t obj_hash(const obj_t* self);\n"
        "obj_t* obj_eval(const obj_t* self, obj_hash_table_t* env);\n"
        "obj_t* obj_apply(const obj_t* self, obj_array_t* args, obj_hash_table_t* env);\n"
        "\n"
        "#endif // OBJ_H\n"
    );
    fprintf(fp_obj_c,
        "#include \"obj.h\"\n"
        "\n"
    );
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
        "obj_type_t obj_get_type(const obj_t* self) {\n"
        "    return self->type;\n"
        "}\n"
        "\n"
        "void obj_to_string(const obj_t* self, str_t* str) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": obj_%s_to_string((obj_%s_t*)self, str); break;\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "ffi_type* obj_to_ffi_type(const obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_to_ffi_type((obj_%s_t*)self);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_copy(const obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_copy((obj_%s_t*)self);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "bool obj_equal(const obj_t* self, const obj_t* other) {\n"
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
        fprintf(fp_obj_c, ": return obj_%s_equal((obj_%s_t*)self, (obj_%s_t*)other);\n", type_cur->name, type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "size_t obj_hash(const obj_t* self) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_hash((obj_%s_t*)self);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_eval(const obj_t* self, obj_hash_table_t* env) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_eval((obj_%s_t*)self, env);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
        "\n"
        "obj_t* obj_apply(const obj_t* self, obj_array_t* args, obj_hash_table_t* env) {\n"
        "    switch (self->type) {\n"
    );
    type_cur = type_head;
    while (type_cur) {
        fprintf(fp_obj_c, "        case OBJ_TYPE_");
        for (int i = 0; type_cur->name[i]; i++) {
            fputc(toupper(type_cur->name[i]), fp_obj_c);
        }
        fprintf(fp_obj_c, ": return obj_%s_apply((obj_%s_t*)self, args, env);\n", type_cur->name, type_cur->name);
        type_cur = type_cur->next;
    }
    fprintf(fp_obj_c,
        "        default: assert(0);\n"
        "    }\n"
        "}\n"
    );

    fclose(fp_type_names);
    fclose(fp_obj_h);
    fclose(fp_obj_c);

    return 0;
}
