# include "hasher.h"

static hasher_t hasher_create(
    size_t (*hash_function)(const void* key),
    int (*key_compare_function)(const void* key1, const void* key2),
    const void* (*key_function)(const void* entry),
    size_t size
);
static hasher_entry_t* hasher_find(const hasher_t* self, const void* key);
static void hasher_change_size(hasher_t* self, size_t new_size);
static void hasher_grow(hasher_t* self);
static void hasher_shrink(hasher_t* self);

static hasher_t hasher_create(
    size_t (*hash_function)(const void* key),
    int (*key_compare_function)(const void* key1, const void* key2),
    const void* (*key_function)(const void* entry),
    size_t size
) {
    hasher_t self;
    self.fill = 0;
    self.size = size;
    self.hasher_entries = (hasher_entry_t*)malloc(sizeof(hasher_entry_t) * size);
    assert(self.hasher_entries);
    for (size_t i = 0; i < size; ++i) {
        self.hasher_entries[i].type = HASHER_ENTRY_TYPE_EMPTY;
        self.hasher_entries[i].entry = 0;
        self.hasher_entries[i].index = i;
    }
    self.hash_function = hash_function;
    self.key_compare_function = key_compare_function;
    self.key_function = key_function;
    return self;
}

static hasher_entry_t* hasher_find(const hasher_t* self, const void* key) {
    size_t hash = self->hash_function(key);
    size_t index = hash % self->size;
    size_t start = index;
    hasher_entry_t* tombstone = 0;
    while (true) {
        hasher_entry_t* entry = &self->hasher_entries[index];
        switch (entry->type) {
        case HASHER_ENTRY_TYPE_EMPTY: {
            if (tombstone) {
                return tombstone;
            } else {
                return entry;
            }
        } break ;
        case HASHER_ENTRY_TYPE_TOMBSTONE: {
            if (!tombstone) {
                tombstone = entry;
            }
        } break ;
        case HASHER_ENTRY_TYPE_FILLED: {
            if (self->key_compare_function(self->key_function(entry->entry), key) == 0) {
                return entry;
            }
        } break ;
        default: assert(0);
        }
        index = (index + 1) % self->size;
        if (index == start) {
            break ;
        }
    }
    return 0;
}

static void hasher_change_size(hasher_t* self, size_t new_size) {
    hasher_t new_table = hasher_create(self->hash_function, self->key_compare_function, self->key_function, new_size);
    for (size_t i = 0; i < self->size; ++i) {
        hasher_entry_t* entry = &self->hasher_entries[i];
        if (entry->type == HASHER_ENTRY_TYPE_FILLED) {
            hasher_insert(&new_table, entry->entry);
        }
    }
    free(self->hasher_entries);
    self->hasher_entries = new_table.hasher_entries;
    self->size = new_table.size;
    self->fill = new_table.fill;
}

static void hasher_grow(hasher_t* self) {
    while (0.75 <= hasher_load_factor(self)) {
        hasher_change_size(self, self->size * 2);
    }
}

static void hasher_shrink(hasher_t* self) {
    while (16 < self->size && hasher_load_factor(self) <= 0.25) {
        hasher_change_size(self, self->size / 2);
    }
}

hasher_t hasher(
    size_t (*hash_function)(const void* key),
    int (*key_compare_function)(const void* key1, const void* key2),
    const void* (*key_function)(const void* entry)
) {
    return hasher_create(hash_function, key_compare_function, key_function, 16);
}

void hasher_destroy(hasher_t* self) {
    free(self->hasher_entries);
    self->hasher_entries = 0;
    self->size = 0;
    self->fill = 0;
}

hasher_entry_t* hasher_get(const hasher_t* self, const void* key) {
    hasher_entry_t* entry = hasher_find(self, key);
    if (entry && entry->type == HASHER_ENTRY_TYPE_FILLED) {
        return entry;
    }
    return 0;
}

bool hasher_is_empty(hasher_t* self) {
    return self->fill == 0;
}

size_t hasher_size(const hasher_t* self) {
    return self->fill;
}

double hasher_load_factor(const hasher_t* self) {
    if (self->size == 0) {
        return 0;
    }
    return (double)self->fill / (double)self->size;
}

hasher_entry_t* hasher_insert(hasher_t* self, const void* entry) {
    hasher_grow(self);
    hasher_entry_t* hasher_entry = hasher_find(self, self->key_function(entry));
    if (hasher_entry && hasher_entry->type != HASHER_ENTRY_TYPE_FILLED) {
        hasher_entry->entry = entry;
        hasher_entry->type = HASHER_ENTRY_TYPE_FILLED;
        ++self->fill;
        return hasher_entry;
    } else {
        return 0;
    }
}

bool hasher_remove(hasher_t* self, const void* key) {
    hasher_entry_t* hasher_entry = hasher_find(self, key);
    if (hasher_entry && hasher_entry->type == HASHER_ENTRY_TYPE_FILLED) {
        hasher_entry->type = HASHER_ENTRY_TYPE_TOMBSTONE;
        --self->fill;
        hasher_shrink(self);
        return true;
    }
    return false;
}

void hasher_clear(hasher_t* self) {
    for (size_t i = 0; i < self->size; ++i) {
        self->hasher_entries[i].type = HASHER_ENTRY_TYPE_EMPTY;
    }
    self->fill = 0;
}

hasher_entry_t* hasher_first(hasher_t* self) {
    if (hasher_size(self) == 0) {
        return 0;
    }

    for (size_t i = 0; i < self->size; ++i) {
        if (self->hasher_entries[i].type == HASHER_ENTRY_TYPE_FILLED) {
            return &self->hasher_entries[i];
        }
    }
    return 0;
}

hasher_entry_t* hasher_last(hasher_t* self) {
    if (hasher_size(self) == 0) {
        return 0;
    }

    for (size_t i = self->size - 1; 0 < i; --i) {
        if (self->hasher_entries[i].type == HASHER_ENTRY_TYPE_FILLED) {
            return &self->hasher_entries[i];
        }
    }

    if (self->hasher_entries[0].type == HASHER_ENTRY_TYPE_FILLED) {
        return &self->hasher_entries[0];
    }

    return 0;
}

hasher_entry_t* hasher_next(hasher_t* self, hasher_entry_t* entry) {
    if (entry->index + 1 < self->size) {
        for (size_t i = entry->index + 1; i < self->size; ++i) {
            if (self->hasher_entries[i].type == HASHER_ENTRY_TYPE_FILLED) {
                return &self->hasher_entries[i];
            }
        }
    }
    return 0;
}

hasher_entry_t* hasher_prev(hasher_t* self, hasher_entry_t* entry) {
    if (0 < entry->index) {
        for (size_t i = entry->index - 1; 0 < i; --i) {
            if (self->hasher_entries[i].type == HASHER_ENTRY_TYPE_FILLED) {
                return &self->hasher_entries[i];
            }
        }

        if (self->hasher_entries[0].type == HASHER_ENTRY_TYPE_FILLED) {
            return &self->hasher_entries[0];
        }
    }
    return 0;
}
