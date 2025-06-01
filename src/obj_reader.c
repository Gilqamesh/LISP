#include "universe.h"

static void reader_node_init(reader_node_t* self);

static void reader_node_init(reader_node_t* self) {
    memset(self->children, 0, sizeof(self->children));
}

obj_reader_t* obj_reader_new(obj_file_t* file, reader_fn_t default_reader_fn) {
    obj_reader_t* self = (obj_reader_t*) malloc(sizeof(obj_reader_t));
    obj_init((obj_t*) self, OBJ_TYPE_READER);
    self->file = file;
    reader_node_init(&self->reader_node);
    self->default_reader_fn = default_reader_fn;
    return self;
}

void obj_reader_delete(obj_reader_t* self) {
    obj_file_delete(self->file);
    free(self);
}

bool is_reader(const obj_t* self) {
    return self->type == OBJ_TYPE_READER;
}

obj_ffi_t* obj_reader_to_ffi(const obj_reader_t* self) {
    assert(0 && "todo: implement");
}

void obj_reader_to_string(const obj_reader_t* self, obj_string_t* other) {
    obj_string_push_cstr(other, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    obj_string_push_cstr(other, "file: ");
    obj_file_to_string(self->file, other);
    obj_string_push_cstr(other, ", default_reader_fn: ");
    if (self->default_reader_fn) {
        char buffer[256];
        addr_to_string((void*) self->default_reader_fn, buffer, sizeof(buffer));
        obj_string_push_cstr(other, "%s", buffer);
    } else {
        obj_string_push_cstr(other, "none");
    }
    obj_string_push_cstr(other, ">");
}

obj_reader_t* obj_reader_copy(const obj_reader_t* self) {
    obj_reader_t* copy = obj_reader_new(obj_file_copy(self->file), self->default_reader_fn);
    return copy;
}

bool obj_reader_equal(const obj_reader_t* self, const obj_reader_t* other) {
    assert(0 && "todo: implement");
}

bool obj_reader_is_truthy(const obj_reader_t* self) {
  assert(0 && "todo: implement");
}

size_t obj_reader_hash(const obj_reader_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_reader_eval(const obj_reader_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_reader_apply(const obj_reader_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}

obj_t* obj_reader_add_reader_function(obj_reader_t* self, const char* prefix, reader_fn_t reader_fn) {
    reader_node_t* node = &self->reader_node;
    while (*prefix) {
        const size_t child_index = (size_t) *prefix;
        assert(child_index < sizeof(node->children) / sizeof(node->children[0]));
        if (!node->children[child_index]) {
            node->children[child_index] = (reader_node_t*) malloc(sizeof(reader_node_t));
            reader_node_init(node->children[child_index]);
        }
        node = node->children[child_index];
        ++prefix;
    }
    node->reader_fn = reader_fn;
}

obj_t* obj_reader_add_reader_function_char(obj_reader_t* self, char c, reader_fn_t reader_fn) {
    const size_t child_index = c;
    assert(child_index < sizeof(self->reader_node.children) / sizeof(self->reader_node.children[0]));
    if (!self->reader_node.children[child_index]) {
        self->reader_node.children[child_index] = (reader_node_t*)malloc(sizeof(reader_node_t));
        reader_node_init(self->reader_node.children[child_index]);
    }
    self->reader_node.children[child_index]->reader_fn = reader_fn;
}

obj_t* obj_reader_read(obj_reader_t* self) {
    if (obj_file_is_at_end(self->file)) {
        return (obj_t*) obj_eof_new();
    }

    reader_node_t* node = &self->reader_node;
    reader_fn_t reader_fn = 0;
    obj_string_t* lexeme = obj_string_new();
    while (node && !obj_file_is_at_end(self->file)) {
        char c = obj_file_read_char(self->file);
        obj_string_push_cstr(lexeme, "%c", c);
        const size_t child_index = (size_t) c;
        assert(child_index <= sizeof(node->children) / sizeof(node->children[0]));
        node = node->children[child_index];
        if (node && node->reader_fn) {
            reader_fn = node->reader_fn;
            obj_string_clear(lexeme);
        }
    }

    obj_t* result = 0;
    if (reader_fn) {
        while (obj_string_size(lexeme)) {
            char c = obj_string_pop(lexeme);
            obj_file_unread_char(self->file, c);
        }
        result = reader_fn(self, lexeme);
    } else {
        while (!obj_file_is_at_end(self->file)) {
            char c = obj_file_read_char(self->file);
            size_t child_index = (unsigned char)c;
            if (sizeof(self->reader_node.children) / sizeof(self->reader_node.children[0]) <= child_index) {
                assert(0);
            }
            if (self->reader_node.children[child_index]) {
                // if (self->is_top_level) {
                    obj_file_unread_char(self->file, c);
                // }
                break ;
            }
            obj_string_push_cstr(lexeme, "%c", c);
        }
        result = self->default_reader_fn(self, lexeme);
    }

    if (is_void(result)) {
        result = obj_reader_read(self);
    }

    return result;
}
