#include "hash_table.h"
#include "str.h"

static size_t str_hash_fn(const void* key) {
    const str_t* str = (const str_t*)key;
    return str_hash(str);
}

static bool str_compare_fn(const void* key1, const void* key2) {
    const str_t* s1 = (const str_t*)key1;
    const str_t* s2 = (const str_t*)key2;
    return str_cmp_str(s1, s2);
}

static const void* entry_key(const void* entry) {
    return entry;
}

int main() {
    hash_table_t table = hash_table_new(sizeof(str_t), 0, str_hash_fn, str_compare_fn);

    assert(hash_table_size(&table) == 0);

    str_t key1 = str_create_cstr("key1");
    hash_table_insert(&table, &key1, 0);
    assert(hash_table_size(&table) == 1);

    str_t key2 = str_create_cstr("key2");
    hash_table_insert(&table, &key2, 0);
    assert(hash_table_size(&table) == 2);

    hash_table_entry_t* entry = hash_table_find(&table, &key1);
    assert(entry);
    assert(entry->is_taken);
    assert(str_cmp_str((str_t*)hash_table_entry_key(&table, entry), &key1));

    hash_table_entry_t* first = hash_table_first(&table);
    while (first) {
        assert(first->is_taken);
        assert(str_cmp_str((str_t*)hash_table_entry_key(&table, entry), &key1) || 
               str_cmp_str((str_t*)hash_table_entry_key(&table, entry), &key2));
        first = hash_table_next(&table, first);
    }

    hash_table_entry_t* last = hash_table_last(&table);
    while (last) {
        assert(last->is_taken);
        assert(str_cmp_str((str_t*)hash_table_entry_key(&table, entry), &key1) || 
               str_cmp_str((str_t*)hash_table_entry_key(&table, entry), &key2));
        last = hash_table_prev(&table, last);
    }

    bool r = hash_table_remove(&table, &key1);
    assert(r);
    assert(hash_table_size(&table) == 1);

    hash_table_clear(&table);
    assert(hash_table_size(&table) == 0);

    const int size = 100000;
    str_t* keys = (str_t*) malloc(size * sizeof(str_t));

    for (size_t i = 0; i < size; ++i) {
        keys[i] = str_create_cstr("key%zu", i);
    }

    srand(42);
    const size_t n_operations = size * 100;
    size_t expected_size = hash_table_size(&table);
    for (size_t i = 0; i < n_operations; ++i) {
        bool insert = rand() % 2 == 0;
        if (insert) {
            size_t index = rand() % size;
            hash_table_insert_result_t result = hash_table_insert(&table, keys + index, 0);
            if (result.is_new) {
                ++expected_size;
            }
        } else {
            if (expected_size == 0) {
                continue ;
            }
            size_t index = rand() % size;
            if (hash_table_remove(&table, keys + index)) {
                assert(expected_size);
                --expected_size;
            }
        }
        assert(hash_table_size(&table) == expected_size);
    }

    hash_table_delete(&table);

    return 0;
}
