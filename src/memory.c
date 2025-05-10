#include "memory.h"
#include "err.h"

static size_t interned_entries_key_hash(const void* key);
static int interned_entries_key_compare(const void* key1, const void* key2);
static const void* interned_entries_entry_key(const void* entry);
static interned_entry_t* interned_entries_insert(memory_t* self, str_t s, obj_t* obj);
static void interned_entries_remove(memory_t* self, size_t index);

static size_t interned_entries_key_hash(const void* key) {
    const str_t* s = (const str_t*)key;
    size_t hash = 5381;
    const size_t s_size = str_size(s);
    for (size_t i = 0; i < s_size; ++i) {
        hash = ((hash << 5) + hash) + str_at(s, i);
    }
    return hash;
}

static int interned_entries_key_compare(const void* key1, const void* key2) {
    const str_t* s1 = (const str_t*)key1;
    const str_t* s2 = (const str_t*)key2;
    return str_is_equal_str(s1, s2) ? 0 : 1;
}

static const void* interned_entries_entry_key(const void* entry) {
    return &((interned_entry_t*)entry)->s;
}

static interned_entry_t* interned_entries_insert(memory_t* self, str_t s, obj_t* obj) {
    if (self->interned_entries_top == self->interned_entries_size) {
        size_t old_size = self->interned_entries_size;
        self->interned_entries_size *= 2;
        self->interned_entries = realloc(self->interned_entries, sizeof(*self->interned_entries) * self->interned_entries_size);
        for (size_t i = old_size; i < self->interned_entries_size; ++i) {
            self->interned_entries[i] = malloc(sizeof(interned_entry_t));
            self->interned_entries[i]->index = i;
        }
    }
    interned_entry_t* interned_entry = self->interned_entries[self->interned_entries_top];
    interned_entry->s = s;
    interned_entry->obj = obj;
    interned_entry->index = self->interned_entries_top;
    ++self->interned_entries_top;
    return interned_entry;
}

static void interned_entries_remove(memory_t* self, size_t index) {
    assert(index < self->interned_entries_top);
    self->interned_entries[index] = self->interned_entries[self->interned_entries_top - 1];
    self->interned_entries[index]->index = index;
    str_destroy(&self->interned_entries[self->interned_entries_top - 1]->s);
    --self->interned_entries_top;

    const double load_factor = (double)self->interned_entries_top / (double)self->interned_entries_size;
    if (16 < self->interned_entries_size && load_factor < 0.25) {
        self->interned_entries_size /= 2;
        self->interned_entries = realloc(self->interned_entries, sizeof(*self->interned_entries) * self->interned_entries_size);
    }
}

void memory_init(memory_t* self) {
    memset(self, 0, sizeof(memory_t));

    self->total_allocated = 0;

    self->obj_eof = (obj_eof_t*)malloc(sizeof(obj_eof_t));
    self->total_allocated += sizeof(obj_eof_t);
    obj_eof_init(self->obj_eof);

    self->obj_nil = (obj_nil_t*)malloc(sizeof(obj_nil_t));
    self->total_allocated += sizeof(obj_nil_t);
    obj_nil_init(self->obj_nil);

    self->obj_void = (obj_void_t*)malloc(sizeof(obj_void_t));
    self->total_allocated += sizeof(obj_void_t);
    obj_void_init(self->obj_void);

    self->obj_true = (obj_bool_t*)malloc(sizeof(obj_bool_t));
    self->total_allocated += sizeof(obj_bool_t);
    obj_bool_init(self->obj_true, true);

    self->obj_false = (obj_bool_t*)malloc(sizeof(obj_bool_t));
    self->total_allocated += sizeof(obj_bool_t);
    obj_bool_init(self->obj_false, false);

    self->interned_entries_size = 16;
    self->interned_entries_top = 0;
    self->interned_entries = malloc(sizeof(*self->interned_entries) * self->interned_entries_size);
    for (size_t i = 0; i < self->interned_entries_size; ++i) {
        self->interned_entries[i] = malloc(sizeof(interned_entry_t));
        self->interned_entries[i]->index = i;
    }
    self->interned_symbols = hasher(
        interned_entries_key_hash,
        interned_entries_key_compare,
        interned_entries_entry_key
    );
}

void memory_destroy(memory_t* self) {
    free(self->obj_eof);
    free(self->obj_nil);
    free(self->obj_void);
    free(self->obj_true);
    free(self->obj_false);
    for (size_t i = 0; i < self->interned_entries_top; ++i) {
        str_destroy(&self->interned_entries[i]->s);
    }
    hasher_destroy(&self->interned_symbols);
}

size_t memory_total_allocated(memory_t* self) {
    return self->total_allocated;
}

obj_t* memory_error(memory_t* self, str_t message) {
    obj_error_t* obj_error = (obj_error_t*)malloc(sizeof(obj_error_t));
    self->total_allocated += sizeof(obj_error_t);
    obj_error_init(obj_error, message);
    return (obj_t*) obj_error;
}

obj_t* memory_eof(memory_t* self) {
    return (obj_t*) self->obj_eof;
}

obj_t* memory_nil(memory_t* self) {
    return (obj_t*) self->obj_nil;
}

obj_t* memory_void(memory_t* self) {
    return (obj_t*) self->obj_void;
}

obj_t* memory_bool(memory_t* self, bool boolean) {
    return boolean ? (obj_t*) self->obj_true : (obj_t*) self->obj_false;
}

obj_t* memory_cons(memory_t* self, obj_t* car, obj_t* cdr) {
    obj_cons_t* obj_cons = (obj_cons_t*)malloc(sizeof(obj_cons_t));
    self->total_allocated += sizeof(obj_cons_t);
    obj_cons_init(obj_cons, car, cdr);
    return (obj_t*) obj_cons;
}

obj_t* memory_real(memory_t* self, double real) {
    obj_real_t* obj_real = (obj_real_t*)malloc(sizeof(obj_real_t));
    self->total_allocated += sizeof(obj_real_t);
    obj_real_init(obj_real, real);
    return (obj_t*) obj_real;
}

obj_t* memory_symbol(memory_t* self, str_t symbol) {
    hasher_entry_t* entry = hasher_find(&self->interned_symbols, &symbol);
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        return interned_entry->obj;
    }
    obj_symbol_t* obj_symbol = (obj_symbol_t*)malloc(sizeof(obj_symbol_t));
    self->total_allocated += sizeof(obj_symbol_t);
    obj_symbol_init(obj_symbol, symbol);
    hasher_insert(&self->interned_symbols, interned_entries_insert(self, symbol, (obj_t*) obj_symbol));
    return (obj_t*) obj_symbol;
}

obj_t* memory_string(memory_t* self, str_t string) {
    obj_string_t* obj_string = (obj_string_t*)malloc(sizeof(obj_string_t));
    self->total_allocated += sizeof(obj_string_t);
    obj_string_init(obj_string, string);
    return (obj_t*) obj_string;
}

obj_t* memory_file(memory_t* self, FILE* file) {
    obj_file_t* obj_file = (obj_file_t*)malloc(sizeof(obj_file_t));
    self->total_allocated += sizeof(obj_file_t);
    obj_file_init(obj_file, file);
    return (obj_t*) obj_file;
}

obj_t* memory_env(memory_t* self) {
    obj_env_t* obj_env = (obj_env_t*)malloc(sizeof(obj_env_t));
    self->total_allocated += sizeof(obj_env_t);
    hasher_t bindings = hasher(
        interned_entries_key_hash,
        interned_entries_key_compare,
        interned_entries_entry_key
    );
    obj_env_init(obj_env, 0, bindings);
    return (obj_t*) obj_env;
}

obj_t* get_env_binding(memory_t* memory, obj_t* obj, obj_t* key) {
    assert(is_env(obj));
    assert(is_symbol(key));
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        return interned_entry->obj;
    }
    obj_t* parent = get_env_parent(obj);
    if (parent) {
        return get_env_binding(memory, parent, key);
    }
    return 0;
}

obj_t* set_env_binding(memory_t* memory, obj_t* obj, obj_t* key, obj_t* value) {
    assert(is_env(obj));
    assert(is_symbol(key));
    assert(value);
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        interned_entry->obj = value;
        return value;
    }

    obj_t* parent = get_env_parent(obj);
    if (parent) {
        return set_env_binding(memory, parent, key, value);
    }
    return err(str_create("set_env_binding: Binding not found"), obj, key, value);
}

obj_t* define_env_binding(memory_t* memory, obj_t* obj, obj_t* key, obj_t* value) {
    assert(is_env(obj));
    assert(is_symbol(key));
    assert(value);
    hasher_entry_t* entry = hasher_find(get_env_bindings(obj), get_symbol(key));
    if (entry) {
        interned_entry_t* interned_entry = (interned_entry_t*) entry->entry;
        interned_entry->obj = value;
        return value;
    }

    interned_entry_t* interned_entry = interned_entries_insert(memory, str_create_str(get_symbol(key)), value);
    hasher_insert(get_env_bindings(obj), interned_entry);
    return value;
}

obj_t* memory_macro(memory_t* self, obj_t* params, obj_t* body) {
    obj_macro_t* obj_macro = (obj_macro_t*)malloc(sizeof(obj_macro_t));
    self->total_allocated += sizeof(obj_macro_t);
    obj_macro_init(obj_macro, params, body);
    return (obj_t*) obj_macro;
}

obj_t* memory_primitive(memory_t* self, str_t name, primitive_t primitive) {
    obj_primitive_t* obj_primitive = (obj_primitive_t*)malloc(sizeof(obj_primitive_t));
    self->total_allocated += sizeof(obj_primitive_t);
    obj_primitive_init(obj_primitive, name, primitive);
    return (obj_t*) obj_primitive;
}

obj_t* memory_compound(memory_t* self, obj_t* params, obj_t* body, obj_t* env) {
    obj_compound_t* obj_compound = (obj_compound_t*)malloc(sizeof(obj_compound_t));
    self->total_allocated += sizeof(obj_compound_t);
    obj_compound_init(obj_compound, params, body, env);
    return (obj_t*) obj_compound;
}
