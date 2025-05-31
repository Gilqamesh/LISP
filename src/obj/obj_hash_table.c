#include "universe.h"

static obj_hash_table_t obj_hash_table_new_internal(size_t entries_size);
static double obj_hash_table_load_factor(const obj_hash_table_t* self);
static void obj_hash_table_change_size(obj_hash_table_t* self, size_t new_entries_size);
static void obj_hash_table_grow(obj_hash_table_t* self);
static void obj_hash_table_shrink(obj_hash_table_t* self);

static obj_hash_table_t obj_hash_table_new_internal(size_t entries_size) {
    assert(entries_size && !(entries_size & (entries_size - 1)) && "must be power of 2");
    obj_hash_table_t self;
    self.entries_fill = 0;
    self.entries_size = entries_size;
    self.entries = (hash_table_entry_t*) calloc(sizeof(*self.entries), entries_size);
    assert(self.entries != NULL);
    for (size_t i = 0; i < self.entries_size; ++i) {
        self.entries[i].index = i;
    }
    return self;
}

static double obj_hash_table_load_factor(const obj_hash_table_t* self) {
    if (self->entries_size == 0) {
        return 1.0;
    }
    return (double)self->entries_fill / (double)self->entries_size;
}

static void obj_hash_table_change_size(obj_hash_table_t* self, size_t new_entries_size) {
    obj_hash_table_t new_table = obj_hash_table_new_internal(new_entries_size);
    for (size_t i = 0; i < self->entries_size; ++i) {
        hash_table_entry_t* entry = self->entries + i;
        if (entry->is_taken) {
            obj_hash_table_insert(&new_table, entry->key, entry->value);
        }
    }
    if (self->entries) {
        free(self->entries);
    }
    self->entries = new_table.entries;
    self->entries_size = new_table.entries_size;
    self->entries_fill = new_table.entries_fill;
}

static void obj_hash_table_grow(obj_hash_table_t* self) {
    while (0.5 <= obj_hash_table_load_factor(self)) {
        obj_hash_table_change_size(self, self->entries_size * 2);
    }
}

static void obj_hash_table_shrink(obj_hash_table_t* self) {
    while (16 < self->entries_size && obj_hash_table_load_factor(self) <= 0.25) {
        obj_hash_table_change_size(self, self->entries_size / 2);
    }
}

obj_hash_table_t* obj_hash_table_new() {
    obj_hash_table_t* self = (obj_hash_table_t*) malloc(sizeof(obj_hash_table_t));
    obj_init((obj_t*) self, OBJ_TYPE_HASH_TABLE);
    *self = obj_hash_table_new_internal(16);
    return self;
}

void obj_hash_table_delete(obj_hash_table_t* self) {
    if (self->entries) {
        free(self->entries);
    }
    free(self);
}

bool is_hash_table(const obj_t* self) {
    return self->type == OBJ_TYPE_HASH_TABLE;
}

obj_ffi_t* obj_hash_table_to_ffi(const obj_hash_table_t* self) {
    assert(0 && "todo: implement");
}

void obj_hash_table_to_string(const obj_hash_table_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<hash_table ", obj_type_to_string(obj_get_type((obj_t*) self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(str, ">");
}

obj_hash_table_t* obj_hash_table_copy(const obj_hash_table_t* self) {
    obj_hash_table_t* copy = obj_hash_table_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_hash_table_equal(const obj_hash_table_t* self, const obj_hash_table_t* other) {
    assert(0 && "todo: implement");
}

size_t obj_hash_table_hash(const obj_hash_table_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_hash_table_eval(const obj_hash_table_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_hash_table_apply(const obj_hash_table_t* self, obj_array_t* args, obj_env_t* env) {
    assert(0 && "todo: implement");
}

hash_table_insert_result_t obj_hash_table_insert(obj_hash_table_t* self, const obj_t* key, obj_t* value) {
    obj_hash_table_grow(self);
    size_t hash = obj_hash(key);
    size_t index = hash & (self->entries_size - 1);
    size_t probe_distance = 0;
    hash_table_insert_result_t result = { 0 };
    while (true) {
        hash_table_entry_t* entry = self->entries + index;
        if (entry->is_taken) {
            if (obj_equal(entry->key, key)) {
                entry->value = value;
                entry->probe_distance = probe_distance;
                result.entry = entry;
                break ;
            }
            if (entry->probe_distance < probe_distance) {
                if (!result.entry) {
                    result.entry = entry;
                }
                const obj_t* tmp_key = entry->key;
                obj_t* tmp_value = entry->value;
                size_t tmp_probe_distance = entry->probe_distance;
                entry->key = key;
                entry->value = value;
                entry->probe_distance = probe_distance;
                key = tmp_key;
                value = tmp_value;
                probe_distance = tmp_probe_distance;
            }
        } else {
            ++self->entries_fill;
            entry->key = key;
            entry->value = value;
            entry->is_taken = true;
            entry->probe_distance = probe_distance;
            result.entry = entry;
            result.is_new = true;
            break ;
        }
        ++probe_distance;
        index = (index + 1) & (self->entries_size - 1);
    }
    return result;
}

hash_table_entry_t* obj_hash_table_find(const obj_hash_table_t* self, const obj_t* key) {
    size_t hash = obj_hash(key);
    size_t index = hash & (self->entries_size - 1);
    size_t probe_distance = 0;
    while (true) {
        hash_table_entry_t* entry = self->entries + index;
        if (!entry->is_taken) {
            break ;
        }

        if (obj_equal(entry->key, key)) {
            return entry;
        }

        if (entry->probe_distance < probe_distance) {
            break ;
        }

        ++probe_distance;
        index = (index + 1) & (self->entries_size - 1);
    }
    return NULL;
}

bool obj_hash_table_remove(obj_hash_table_t* self, const obj_t* key) {
    hash_table_entry_t* entry = obj_hash_table_find(self, key);
    if (entry) {
        --self->entries_fill;
        entry->is_taken = false;
        entry->key = 0;
        entry->value = 0;
        entry->probe_distance = 0;

        size_t index = (entry->index + 1) & (self->entries_size - 1);
        hash_table_entry_t* prev_entry = entry;
        while (true) {
            entry = self->entries + index;

            if (!entry->is_taken || entry->probe_distance == 0) {
                break ;
            }

            prev_entry->key = entry->key;
            prev_entry->value = entry->value;
            prev_entry->probe_distance = entry->probe_distance - 1;
            entry->is_taken = false;
            prev_entry->is_taken = true;
            prev_entry = entry;
            index = (index + 1) & (self->entries_size - 1);
        }

        obj_hash_table_shrink(self);
        return true;
    }
    return false;
}

void obj_hash_table_clear(obj_hash_table_t* self) {
    obj_hash_table_t hash_table = obj_hash_table_new_internal(16);
    if (self->entries) {
        free(self->entries);
    }
    self->entries = hash_table.entries;
    self->entries_size = hash_table.entries_size;
    self->entries_fill = hash_table.entries_fill;
}

size_t obj_hash_table_size(const obj_hash_table_t* self) {
    return self->entries_fill;
}

hash_table_entry_t* obj_hash_table_first(const obj_hash_table_t* self) {
    if (self->entries_size == 0) {
        return NULL;
    }

    for (size_t i = 0; i < self->entries_size; ++i) {
        hash_table_entry_t* entry = self->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_last(const obj_hash_table_t* self) {
    if (self->entries_size == 0) {
        return NULL;
    }

    for (size_t i = self->entries_size - 1; 0 < i; --i) {
        hash_table_entry_t* entry = self->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    hash_table_entry_t* entry = self->entries;
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_next(const obj_hash_table_t* self, hash_table_entry_t* entry) {
    for (size_t i = entry->index + 1; i < self->entries_size; ++i) {
        entry = self->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_prev(const obj_hash_table_t* self, hash_table_entry_t* entry) {
    if (entry->index == 0) {
        return NULL;
    }

    for (size_t i = entry->index - 1; 0 < i; --i) {
        entry = self->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    entry = self->entries;
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}
