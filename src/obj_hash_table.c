#include "universe.h"

static obj_hash_table_t obj_hash_table_new_internal(size_t entries_size);
static double obj_hash_table_load_factor(obj_hash_table_t* self);
static void obj_hash_table_change_size(obj_hash_table_t* self, size_t new_entries_size);
static void obj_hash_table_grow(obj_hash_table_t* self);
static void obj_hash_table_shrink(obj_hash_table_t* self);

static obj_hash_table_t obj_hash_table_new_internal(size_t entries_size) {
    assert(entries_size && !(entries_size & (entries_size - 1)) && "must be power of 2");
    obj_hash_table_t self;
    obj_init((obj_t*) &self, OBJ_TYPE_HASH_TABLE);
    self.entries_fill = 0;
    self.entries_size = entries_size;
    self.entries = (hash_table_entry_t*) calloc(sizeof(*self.entries), entries_size);
    assert(self.entries != NULL);
    for (size_t i = 0; i < self.entries_size; ++i) {
        self.entries[i].index = i;
    }
    return self;
}

static double obj_hash_table_load_factor(obj_hash_table_t* self) {
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
            obj_hash_table_insert((obj_t*) &new_table, entry->key, entry->value);
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

obj_t* obj_hash_table_new() {
    obj_hash_table_t* self = (obj_hash_table_t*) malloc(sizeof(obj_hash_table_t));
    obj_hash_table_t table = obj_hash_table_new_internal(16);
    memcpy(self, &table, sizeof(obj_hash_table_t));
    return (obj_t*) self;
}

void obj_hash_table_delete(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    if (hash_table->entries) {
        free(hash_table->entries);
    }
    free(hash_table);
}

bool is_hash_table(obj_t* self) {
    return self->type == OBJ_TYPE_HASH_TABLE;
}

obj_hash_table_t* obj_as_hash_table(obj_t* self) {
    if (!is_hash_table(self)) {
        throw(obj_string_new_cstr("expected obj_hash_table_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_hash_table_t*) self;
}

ffi_type* obj_hash_table_to_ffi(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    assert(0 && "todo: implement");
}

void obj_hash_table_to_string(obj_t* self, obj_t* string) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    assert(0 && "todo: implement");
    obj_string_push_cstr(string, ">");
}

obj_t* obj_hash_table_copy(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    obj_t* copy = obj_hash_table_new();
    assert(0 && "todo: implement");
    return copy;
}

bool obj_hash_table_is_equal(obj_t* self, obj_t* other) {
    obj_hash_table_t* hash_table_self = obj_as_hash_table(self);
    obj_hash_table_t* hash_table_other = obj_as_hash_table(other);
    assert(0 && "todo: implement");
}

bool obj_hash_table_is_truthy(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
  assert(0 && "todo: implement");
}

size_t obj_hash_table_hash(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    assert(0 && "todo: implement");
}

obj_t* obj_hash_table_eval(obj_t* self, obj_t* env) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    return self;
}

obj_t* obj_hash_table_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

hash_table_insert_result_t obj_hash_table_insert(obj_t* self, obj_t* key, obj_t* value) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    obj_hash_table_grow(hash_table);
    size_t hash = obj_hash(key);
    size_t index = hash & (hash_table->entries_size - 1);
    size_t probe_distance = 0;
    hash_table_insert_result_t result = { 0 };
    while (true) {
        hash_table_entry_t* entry = hash_table->entries + index;
        if (entry->is_taken) {
            if (obj_is_equal(entry->key, key)) {
                entry->value = value;
                entry->probe_distance = probe_distance;
                result.entry = entry;
                break ;
            }
            if (entry->probe_distance < probe_distance) {
                if (!result.entry) {
                    result.entry = entry;
                }
                obj_t* tmp_key = entry->key;
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
            ++hash_table->entries_fill;
            entry->key = key;
            entry->value = value;
            entry->is_taken = true;
            entry->probe_distance = probe_distance;
            result.entry = entry;
            result.is_new = true;
            break ;
        }
        ++probe_distance;
        index = (index + 1) & (hash_table->entries_size - 1);
    }
    return result;
}

hash_table_entry_t* obj_hash_table_find(obj_t* self, obj_t* key) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    size_t hash = obj_hash(key);
    size_t index = hash & (hash_table->entries_size - 1);
    size_t probe_distance = 0;
    while (true) {
        hash_table_entry_t* entry = hash_table->entries + index;
        if (!entry->is_taken) {
            break ;
        }

        if (obj_is_equal(entry->key, key)) {
            return entry;
        }

        if (entry->probe_distance < probe_distance) {
            break ;
        }

        ++probe_distance;
        index = (index + 1) & (hash_table->entries_size - 1);
    }
    return NULL;
}

bool obj_hash_table_remove(obj_t* self, obj_t* key) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    hash_table_entry_t* entry = obj_hash_table_find(self, key);
    if (entry) {
        --hash_table->entries_fill;
        entry->is_taken = false;
        entry->key = 0;
        entry->value = 0;
        entry->probe_distance = 0;

        size_t index = (entry->index + 1) & (hash_table->entries_size - 1);
        hash_table_entry_t* prev_entry = entry;
        while (true) {
            entry = hash_table->entries + index;

            if (!entry->is_taken || entry->probe_distance == 0) {
                break ;
            }

            prev_entry->key = entry->key;
            prev_entry->value = entry->value;
            prev_entry->probe_distance = entry->probe_distance - 1;
            entry->is_taken = false;
            prev_entry->is_taken = true;
            prev_entry = entry;
            index = (index + 1) & (hash_table->entries_size - 1);
        }

        obj_hash_table_shrink(hash_table);
        return true;
    }
    return false;
}

void obj_hash_table_clear(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    obj_hash_table_t new_hash_table = obj_hash_table_new_internal(16);
    if (hash_table->entries) {
        free(hash_table->entries);
    }
    hash_table->entries = new_hash_table.entries;
    hash_table->entries_size = new_hash_table.entries_size;
    hash_table->entries_fill = new_hash_table.entries_fill;
}

size_t obj_hash_table_size(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    return hash_table->entries_fill;
}

hash_table_entry_t* obj_hash_table_first(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    if (hash_table->entries_size == 0) {
        return NULL;
    }

    for (size_t i = 0; i < hash_table->entries_size; ++i) {
        hash_table_entry_t* entry = hash_table->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_last(obj_t* self) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    if (hash_table->entries_size == 0) {
        return NULL;
    }

    for (size_t i = hash_table->entries_size - 1; 0 < i; --i) {
        hash_table_entry_t* entry = hash_table->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    hash_table_entry_t* entry = hash_table->entries;
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_next(obj_t* self, hash_table_entry_t* entry) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    for (size_t i = entry->index + 1; i < hash_table->entries_size; ++i) {
        entry = hash_table->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* obj_hash_table_prev(obj_t* self, hash_table_entry_t* entry) {
    obj_hash_table_t* hash_table = obj_as_hash_table(self);
    if (entry->index == 0) {
        return NULL;
    }

    for (size_t i = entry->index - 1; 0 < i; --i) {
        entry = hash_table->entries + i;
        if (entry->is_taken) {
            return entry;
        }
    }

    entry = hash_table->entries;
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}
