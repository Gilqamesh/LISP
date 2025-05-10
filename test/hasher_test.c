#include "hasher_test.h"
#include "hasher.h"

#include "str.h"

static size_t str_hash(const void* key) {
    const str_t* s = (const str_t*)key;
    size_t hash = 5381;
    const size_t s_size = str_size(s);
    for (size_t i = 0; i < s_size; ++i) {
        hash = ((hash << 5) + hash) + str_at(s, i);
    }
    return hash;
}

static int str_compare(const void* key1, const void* key2) {
    const str_t* s1 = (const str_t*)key1;
    const str_t* s2 = (const str_t*)key2;
    return str_is_equal_str(s1, s2) ? 0 : 1;
}

static const void* entry_key(const void* entry) {
    return entry;
}

void hasher_test() {
    hasher_t set = hasher(str_hash, str_compare, entry_key);

    assert(hasher_is_empty(&set));
    assert(hasher_size(&set) == 0);

    str_t key1 = str_create("key1");
    hasher_insert(&set, &key1);
    assert(!hasher_is_empty(&set));
    assert(hasher_size(&set) == 1);

    str_t key2 = str_create("key2");
    hasher_insert(&set, &key2);
    assert(hasher_size(&set) == 2);

    hasher_entry_t* entry = hasher_find(&set, &key1);
    assert(entry);
    assert(entry->type == HASHER_ENTRY_TYPE_FILLED);
    assert(str_is_equal_str((str_t*)entry->entry, &key1));

    hasher_entry_t* first = hasher_first(&set);
    while (first) {
        assert(first->type == HASHER_ENTRY_TYPE_FILLED);
        assert(str_is_equal_str((str_t*)first->entry, &key1) || 
               str_is_equal_str((str_t*)first->entry, &key2));
        first = hasher_next(&set, first);
    }

    hasher_entry_t* last = hasher_last(&set);
    while (last) {
        assert(last->type == HASHER_ENTRY_TYPE_FILLED);
        assert(str_is_equal_str((str_t*)last->entry, &key1) || 
               str_is_equal_str((str_t*)last->entry, &key2));
        last = hasher_prev(&set, last);
    }

    bool r = hasher_remove(&set, &key1);
    assert(r);
    assert(hasher_size(&set) == 1);

    hasher_clear(&set);
    assert(hasher_is_empty(&set));

    const int size = 10000;
    str_t keys[size];

    for (size_t i = 0; i < size; ++i) {
        keys[i] = str_create("key%zu", i);
        hasher_insert(&set, keys + i);
        assert(hasher_size(&set) == i + 1);
        hasher_entry_t* entry = hasher_find(&set, keys + i);
        assert(entry);
        assert(entry->type == HASHER_ENTRY_TYPE_FILLED);
        assert(str_is_equal_str((str_t*)entry->entry, keys + i));
    }

    for (size_t i = 0; i < size; ++i) {
        bool r = hasher_remove(&set, keys + i);
        assert(r);
        assert(hasher_size(&set) == size - 1 - i);
    }

    assert(hasher_is_empty(&set));

    hasher_destroy(&set);
}
