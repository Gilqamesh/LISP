#include "universe.h"

int main(int argc, char** argv) {
    universe_init(argc, argv);

    try {
        obj_t* array = obj_array_new();
        assert(array != NULL);
        assert(is_array(array));
        assert(obj_array_size(array) == 0);
        obj_t* obj1 = obj_string_new_cstr("Hello");
        obj_array_push(array, obj1);
        assert(obj_array_size(array) == 1);
        assert(obj_array_read(array, 0) == obj1);

        obj_t* obj2 = obj_string_new_cstr("World");
        obj_array_push(array, obj2);
        assert(obj_array_size(array) == 2);
        assert(obj_array_read(array, 1) == obj2);
        obj_array_push_array(array, array);
        assert(obj_array_size(array) == 4);
        assert(obj_array_read(array, 2) == obj1);
        assert(obj_array_read(array, 3) == obj2);
        obj_array_pop(array);
        assert(obj_array_size(array) == 3);

        obj_t* array_copy = obj_array_copy(array);
        assert(array_copy != NULL);
        assert(is_array(array_copy));
        assert(obj_array_size(array_copy) == 3);
        assert(obj_is_equal(obj_array_read(array_copy, 0), obj1));
        assert(obj_is_equal(obj_array_read(array_copy, 1), obj2));
        assert(obj_is_equal(obj_array_read(array_copy, 2), obj1));
        assert(obj_array_is_equal(array, array_copy));
        obj_array_delete(array_copy);

        obj_array_clear(array);
        assert(obj_array_size(array) == 0);

        obj_array_delete(array);
        obj_string_delete(obj1);
        obj_string_delete(obj2);
    } catch {
        obj_t* err = err_catch_context();
        obj_t* str = obj_string_new();
        obj_to_string(err, str);
        printf("%s\n", obj_string_cstr(str));
        obj_string_delete(str);
    }

    universe_deinit();
}
