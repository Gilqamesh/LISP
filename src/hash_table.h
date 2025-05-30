#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "libc.h"

typedef struct hash_table_entry_t {
    bool is_taken;
    size_t index;
    size_t probe_distance;
    char payload[];
} hash_table_entry_t;

typedef struct hash_table_t {
    size_t size_key;
    size_t size_value;
    size_t entries_fill;
    size_t entries_size;
    hash_table_entry_t* entries;
    void* key_sb_from;
    void* value_sb_from;
    void* key_sb_to;
    void* value_sb_to;
    size_t (*key_hash_fn)(const void* key);
    bool (*key_compare_fn)(const void* key1, const void* key2);
} hash_table_t;

hash_table_t hash_table_new(
    size_t size_key, size_t size_value,
    size_t (*key_hash_fn)(const void* key),
    bool (*key_compare_fn)(const void* key1, const void* key2)
);
void hash_table_delete(hash_table_t* self);

void* hash_table_entry_key(const hash_table_t* self, const hash_table_entry_t* entry);
void* hash_table_entry_value(const hash_table_t* self, const hash_table_entry_t* entry);

typedef struct hash_table_insert_result_t {
    bool is_new;
    hash_table_entry_t* entry;
} hash_table_insert_result_t;
hash_table_insert_result_t hash_table_insert(hash_table_t* self, const void* key, const void* value);
hash_table_entry_t* hash_table_find(const hash_table_t* self, const void* key);
bool hash_table_remove(hash_table_t* self, const void* key);
void hash_table_clear(hash_table_t* self);

size_t hash_table_size_key(const hash_table_t* self);
size_t hash_table_size_value(const hash_table_t* self);
size_t hash_table_size(const hash_table_t* self);

hash_table_entry_t* hash_table_first(const hash_table_t* self);
hash_table_entry_t* hash_table_last(const hash_table_t* self);
hash_table_entry_t* hash_table_next(const hash_table_t* self, hash_table_entry_t* entry);
hash_table_entry_t* hash_table_prev(const hash_table_t* self, hash_table_entry_t* entry);

#endif // HASH_TABLE_H
