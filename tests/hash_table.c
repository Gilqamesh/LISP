#include "universe.h"

int main(int argc, char** argv) {
    universe_init(argc, argv);

    try {
        obj_t* table = obj_hash_table_new();

        assert(obj_hash_table_size(table) == 0);

        obj_t* key1 = obj_string_new_cstr("key1");
        obj_hash_table_insert(table, key1, 0);
        assert(obj_hash_table_size(table) == 1);

        obj_t* key2 = obj_string_new_cstr("key2");
        obj_hash_table_insert(table, key2, 0);
        assert(obj_hash_table_size(table) == 2);

        hash_table_entry_t* entry = obj_hash_table_find(table, key1);
        assert(entry);
        assert(entry->is_taken);
        assert(obj_is_equal(entry->key, key1));

        hash_table_entry_t* first = obj_hash_table_first(table);
        while (first) {
            assert(first->is_taken);
            assert(obj_is_equal(entry->key, key1) || obj_is_equal(entry->key, key2));
            first = obj_hash_table_next(table, first);
        }

        hash_table_entry_t* last = obj_hash_table_last(table);
        while (last) {
            assert(last->is_taken);
            assert(obj_is_equal(entry->key, key1) || obj_is_equal(entry->key, key2));
            last = obj_hash_table_prev(table, last);
        }

        bool r = obj_hash_table_remove(table, key1);
        assert(r);
        assert(obj_hash_table_size(table) == 1);

        obj_hash_table_clear(table);
        assert(obj_hash_table_size(table) == 0);

        const int size = 100000;
        obj_t** keys = (obj_t**) malloc(size * sizeof(obj_string_t*));

        for (size_t i = 0; i < size; ++i) {
            keys[i] = obj_string_new_cstr("key%zu", i);
        }

        srand(42);
        const size_t n_operations = size * 100;
        size_t expected_size = obj_hash_table_size(table);
        for (size_t i = 0; i < n_operations; ++i) {
            bool insert = rand() % 2 == 0;
            if (insert) {
                size_t index = rand() % size;
                hash_table_insert_result_t result = obj_hash_table_insert(table, keys[index], 0);
                if (result.is_new) {
                    ++expected_size;
                }
            } else {
                if (expected_size == 0) {
                    continue ;
                }
                size_t index = rand() % size;
                if (obj_hash_table_remove(table, keys[index])) {
                    assert(expected_size);
                    --expected_size;
                }
            }
            assert(obj_hash_table_size(table) == expected_size);
        }

        obj_hash_table_delete(table);
    } catch {
        obj_t* err = err_catch_context();
        obj_t* str = obj_string_new();
        obj_to_string(err, str);
        printf("%s\n", obj_string_cstr(str));
        obj_string_delete(str);
    }

    universe_deinit();

    return 0;
}
