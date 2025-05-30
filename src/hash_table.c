#include "hash_table.h"

static hash_table_t hash_table_new_internal(
    size_t size_key, size_t size_value,
    size_t (*key_hash_fn)(const void* key),
    bool (*key_compare_fn)(const void* key1, const void* key2),
    size_t initial_size
);
static size_t hash_table_entry_size(const hash_table_t* self);
static hash_table_entry_t* hash_table_at(const hash_table_t* self, size_t index);
static double hash_table_load_factor(const hash_table_t* self);
static void hash_table_change_size(hash_table_t* self, size_t new_size);
static void hash_table_grow(hash_table_t* self);
static void hash_table_shrink(hash_table_t* self);

static hash_table_t hash_table_new_internal(
    size_t size_key, size_t size_value,
    size_t (*key_hash_fn)(const void* key),
    bool (*key_compare_fn)(const void* key1, const void* key2),
    size_t initial_size
) {
    assert(initial_size && !(initial_size & (initial_size - 1)) && "must be power of 2");
    hash_table_t self;
    self.size_key = size_key;
    self.size_value = size_value;
    self.entries_fill = 0;
    self.entries_size = initial_size;
    self.entries = (hash_table_entry_t*) malloc(initial_size * (sizeof(*self.entries) + size_key + size_value));
    self.key_sb_from = malloc(self.size_key);
    self.value_sb_from = malloc(self.size_value);
    self.key_sb_to = malloc(self.size_key);
    self.value_sb_to = malloc(self.size_value);
    assert(self.entries != NULL);
    for (size_t i = 0; i < self.entries_size; ++i) {
        hash_table_entry_t* entry = hash_table_at(&self, i);
        entry->is_taken = false;
        entry->index = i;
        entry->probe_distance = 0;
    }
    self.key_hash_fn = key_hash_fn;
    self.key_compare_fn = key_compare_fn;
    return self;
}

static size_t hash_table_entry_size(const hash_table_t* self) {
    return sizeof(hash_table_entry_t) + self->size_key + self->size_value;
}

static hash_table_entry_t* hash_table_at(const hash_table_t* self, size_t index) {
    assert(index < self->entries_size);
    return (hash_table_entry_t*)((char*)self->entries + index * hash_table_entry_size(self));
}

static double hash_table_load_factor(const hash_table_t* self) {
    if (self->entries_size == 0) {
        return 1.0;
    }
    return (double)self->entries_fill / (double)self->entries_size;
}

static void hash_table_change_size(hash_table_t* self, size_t new_size) {
    hash_table_t new_table = hash_table_new_internal(self->size_key, self->size_value, self->key_hash_fn, self->key_compare_fn, new_size);
    for (size_t i = 0; i < self->entries_size; ++i) {
        hash_table_entry_t* entry = hash_table_at(self, i);
        if (entry->is_taken) {
            hash_table_insert(&new_table, hash_table_entry_key(self, entry), hash_table_entry_value(self, entry));
        }
    }
    hash_table_delete(self);
    memcpy(self, &new_table, sizeof(*self));
}

static void hash_table_grow(hash_table_t* self) {
    while (0.5 <= hash_table_load_factor(self)) {
        hash_table_change_size(self, self->entries_size * 2);
    }
}

static void hash_table_shrink(hash_table_t* self) {
    while (16 < self->entries_size && hash_table_load_factor(self) <= 0.25) {
        hash_table_change_size(self, self->entries_size / 2);
    }
}

void* hash_table_entry_key(const hash_table_t* self, const hash_table_entry_t* entry) {
    return (void*)entry->payload;
}

void* hash_table_entry_value(const hash_table_t* self, const hash_table_entry_t* entry) {
    return (char*)entry->payload + self->size_key;
}

hash_table_t hash_table_new(
    size_t size_key, size_t size_value,
    size_t (*key_hash_fn)(const void* key),
    bool (*key_compare_fn)(const void* key1, const void* key2)
) {
    return hash_table_new_internal(size_key, size_value, key_hash_fn, key_compare_fn, 16);
}

void hash_table_delete(hash_table_t* self) {
    if (self->entries) {
        free(self->entries);
    }
    if (self->key_sb_from) {
        free(self->key_sb_from);
    }
    if (self->value_sb_from) {
        free(self->value_sb_from);
    }
    if (self->key_sb_to) {
        free(self->key_sb_to);
    }
    if (self->value_sb_to) {
        free(self->value_sb_to);
    }
    memset(self, 0, sizeof(*self));
}

hash_table_insert_result_t hash_table_insert(hash_table_t* self, const void* key, const void* value) {
    hash_table_grow(self);
    size_t hash = self->key_hash_fn(key);
    size_t index = hash & (self->entries_size - 1);
    size_t probe_distance = 0;
    memcpy(self->key_sb_from, key, self->size_key);
    memcpy(self->value_sb_from, value, self->size_value);
    hash_table_insert_result_t result = { 0 };
    while (true) {
        hash_table_entry_t* entry = hash_table_at(self, index);
        if (entry->is_taken) {
            if (self->key_compare_fn(hash_table_entry_key(self, entry), self->key_sb_from)) {
                memcpy(hash_table_entry_value(self, entry), self->value_sb_from, self->size_value);
                entry->probe_distance = probe_distance;
                result.entry = entry;
                break ;
            }
            if (entry->probe_distance < probe_distance) {
                if (!result.entry) {
                    result.entry = entry;
                }
                memcpy(self->key_sb_to, hash_table_entry_key(self, entry), self->size_key);
                memcpy(self->value_sb_to, hash_table_entry_value(self, entry), self->size_value);
                memcpy(hash_table_entry_key(self, entry), self->key_sb_from, self->size_key);
                memcpy(hash_table_entry_value(self, entry), self->value_sb_from, self->size_value);
                memcpy(self->key_sb_from, self->key_sb_to, self->size_key);
                memcpy(self->value_sb_from, self->value_sb_to, self->size_value);
                size_t entry_probe_distance = entry->probe_distance;
                entry->probe_distance = probe_distance;
                probe_distance = entry_probe_distance;
            }
        } else {
            memcpy(hash_table_entry_key(self, entry), self->key_sb_from, self->size_key);
            memcpy(hash_table_entry_value(self, entry), self->value_sb_from, self->size_value);
            entry->is_taken = true;
            entry->probe_distance = probe_distance;
            ++self->entries_fill;
            result.entry = entry;
            result.is_new = true;
            break ;
        }
        ++probe_distance;
        index = (index + 1) & (self->entries_size - 1);
    }
    return result;
}

hash_table_entry_t* hash_table_find(const hash_table_t* self, const void* key) {
    size_t hash = self->key_hash_fn(key);
    size_t index = hash & (self->entries_size - 1);
    size_t probe_distance = 0;
    while (true) {
        hash_table_entry_t* entry = hash_table_at(self, index);
        if (!entry->is_taken) {
            break ;
        }

        if (self->key_compare_fn(hash_table_entry_key(self, entry), key)) {
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

bool hash_table_remove(hash_table_t* self, const void* key) {
    hash_table_entry_t* entry = hash_table_find(self, key);
    if (entry) {
        entry->is_taken = false;
        entry->probe_distance = 0;
        --self->entries_fill;

        size_t index = (entry->index + 1) & (self->entries_size - 1);
        hash_table_entry_t* prev_entry = entry;
        while (true) {
            entry = hash_table_at(self, index);

            if (!entry->is_taken || entry->probe_distance == 0) {
                break ;
            }

            memcpy(hash_table_entry_key(self, prev_entry), hash_table_entry_key(self, entry), self->size_key);
            memcpy(hash_table_entry_value(self, prev_entry), hash_table_entry_value(self, entry), self->size_value);
            prev_entry->probe_distance = entry->probe_distance - 1;
            entry->is_taken = false;
            prev_entry->is_taken = true;
            prev_entry = entry;
            index = (index + 1) & (self->entries_size - 1);
        }

        hash_table_shrink(self);
        return true;
    }
    return false;
}

void hash_table_clear(hash_table_t* self) {
    hash_table_t hash_table = hash_table_new(self->size_key, self->size_value, self->key_hash_fn, self->key_compare_fn);
    hash_table_delete(self);
    memcpy(self, &hash_table, sizeof(*self));
}

size_t hash_table_size_key(const hash_table_t* self) {
    return self->size_key;
}

size_t hash_table_size_value(const hash_table_t* self) {
    return self->size_value;
}

size_t hash_table_size(const hash_table_t* self) {
    return self->entries_fill;
}

hash_table_entry_t* hash_table_first(const hash_table_t* self) {
    if (self->entries_size == 0) {
        return NULL;
    }

    for (size_t i = 0; i < self->entries_size; ++i) {
        hash_table_entry_t* entry = hash_table_at(self, i);
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* hash_table_last(const hash_table_t* self) {
    if (self->entries_size == 0) {
        return NULL;
    }

    for (size_t i = self->entries_size - 1; 0 < i; --i) {
        hash_table_entry_t* entry = hash_table_at(self, i);
        if (entry->is_taken) {
            return entry;
        }
    }

    hash_table_entry_t* entry = hash_table_at(self, 0);
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}

hash_table_entry_t* hash_table_next(const hash_table_t* self, hash_table_entry_t* entry) {
    for (size_t i = entry->index + 1; i < self->entries_size; ++i) {
        entry = hash_table_at(self, i);
        if (entry->is_taken) {
            return entry;
        }
    }

    return NULL;
}

hash_table_entry_t* hash_table_prev(const hash_table_t* self, hash_table_entry_t* entry) {
    if (entry->index == 0) {
        return NULL;
    }

    for (size_t i = entry->index - 1; 0 < i; --i) {
        entry = hash_table_at(self, i);
        if (entry->is_taken) {
            return entry;
        }
    }

    entry = hash_table_at(self, 0);
    if (entry->is_taken) {
        return entry;
    }

    return NULL;
}
