#ifndef HASHER_H
# define HASHER_H

# include "libc.h"

typedef enum hasher_entry_type_t {
    HASHER_ENTRY_TYPE_EMPTY,
    HASHER_ENTRY_TYPE_TOMBSTONE,
    HASHER_ENTRY_TYPE_FILLED
} hasher_entry_type_t;

typedef struct hasher_entry_t {
    const void* entry;
    hasher_entry_type_t type;
    size_t index;
} hasher_entry_t;

typedef struct hasher_t {
    size_t fill;
    size_t size;
    hasher_entry_t* hasher_entries;
    size_t (*hash_function)(const void* key);
    int (*key_compare_function)(const void* key1, const void* key2);
    const void* (*key_function)(const void* entry);
} hasher_t;

hasher_t hasher(
    size_t (*hash_function)(const void* key),
    int (*key_compare_function)(const void* key1, const void* key2),
    const void* (*key_function)(const void* entry)
);
void hasher_destroy(hasher_t* self);

hasher_entry_t* hasher_find(const hasher_t* self, const void* key);
bool hasher_is_empty(hasher_t* self);
size_t hasher_size(const hasher_t* self);
double hasher_load_factor(const hasher_t* self);
hasher_entry_t* hasher_insert(hasher_t* self, const void* entry);
bool hasher_remove(hasher_t* self, const void* key);
void hasher_clear(hasher_t* self);

hasher_entry_t* hasher_last(hasher_t* self);
hasher_entry_t* hasher_first(hasher_t* self);
hasher_entry_t* hasher_next(hasher_t* self, hasher_entry_t* entry);
hasher_entry_t* hasher_prev(hasher_t* self, hasher_entry_t* entry);

#endif // hasher_H
