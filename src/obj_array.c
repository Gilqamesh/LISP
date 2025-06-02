#include "universe.h"

typedef obj_t* obj_array_element_t;

static double obj_array_load_factor(obj_array_t* self);
static void obj_array_change_size(obj_array_t* self, size_t new_size);
static void obj_array_grow(obj_array_t* self);
static void obj_array_shrink(obj_array_t* self);

static double obj_array_load_factor(obj_array_t* self) {
    if (self->objs_capacity == 0) {
        return 1.0;
    }
    return (double)self->objs_fill / (double)self->objs_capacity;
}

static void obj_array_change_size(obj_array_t* self, size_t new_size) {
    assert(new_size && !(new_size & (new_size - 1)) && "must be power of 2");
    if (self->objs_capacity == new_size) {
        return ;
    }
    if (self->objs) {
        self->objs = realloc(self->objs, new_size * sizeof(*self->objs));
    } else {
        self->objs = malloc(new_size * sizeof(*self->objs));
    }
    assert(self->objs != NULL);
    self->objs_capacity = new_size;
    if (self->objs_capacity < self->objs_fill) {
        self->objs_fill = self->objs_capacity;
    }
}

static void obj_array_grow(obj_array_t* self) {
    if (self->objs_fill < self->objs_capacity) {
        return ;
    }
    obj_array_change_size(self, self->objs_capacity ? self->objs_capacity * 2 : 16);
}

static void obj_array_shrink(obj_array_t* self) {
    if (16 < self->objs_capacity && obj_array_load_factor(self) < 0.5) {
        obj_array_change_size(self, self->objs_capacity / 2);
    }
}

obj_t* obj_array_new() {
    obj_array_t* self = (obj_array_t*) malloc(sizeof(obj_array_t));
    obj_init((obj_t*) self, OBJ_TYPE_ARRAY);
    self->objs_capacity = 0;
    self->objs_fill = 0;
    self->objs = NULL;
    return (obj_t*) self;
}

void obj_array_delete(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    if (obj_array->objs) {
        free(obj_array->objs);
    }
    free(self);
}

bool is_array(obj_t* self) {
    return self->type == OBJ_TYPE_ARRAY;
}

obj_array_t* obj_as_array(obj_t* self) {
    if (!is_array(self)) {
        throw(obj_string_new_cstr("expected obj_array_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_array_t*) self;
}

ffi_type* obj_array_to_ffi(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    assert(0 && "todo: implement");
}

void obj_array_to_string(obj_t* self, obj_t* string) {
    obj_array_t* obj_array = obj_as_array(self);
    obj_string_push_cstr(string, "<%s ", obj_type_to_string(obj_get_type(self)));
    if (obj_array->objs_fill) {
        obj_string_push_cstr(string, " ");
    }
    for (size_t i = 0; i < obj_array->objs_fill; ++i) {
        obj_to_string(obj_array->objs[i], string);
        if (i + 1 < obj_array->objs_fill) {
            obj_string_push_cstr(string, ", ");
        }
    }
    obj_string_push_cstr(string, ">");
}

obj_t* obj_array_copy(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    obj_t* copy = obj_array_new();
    for (size_t i = 0; i < obj_array->objs_fill; ++i) {
        obj_array_push(copy, obj_copy(obj_array->objs[i]));
    }
    return copy;
}

bool obj_array_is_equal(obj_t* self, obj_t* other) {
    obj_array_t* obj_array_self = obj_as_array(self);
    obj_array_t* obj_array_other = obj_as_array(other);
    if (obj_array_self->objs_fill != obj_array_other->objs_fill) {
        return false;
    }
    for (size_t i = 0; i < obj_array_self->objs_fill; ++i) {
        if (!obj_is_equal(obj_array_self->objs[i], obj_array_other->objs[i])) {
            return false;
        }
    }
    return true;
}

bool obj_array_is_truthy(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    return 0 < obj_array_size(self);
}


size_t obj_array_hash(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    assert(0 && "todo: implement");
}

obj_t* obj_array_eval(obj_t* self, obj_t* env) {
    obj_array_t* obj_array = obj_as_array(self);
    return (obj_t*) self;
}

obj_t* obj_array_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_array_t* obj_array = obj_as_array(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}

obj_t* obj_array_push(obj_t* self, obj_t* obj) {
    obj_array_t* obj_array = obj_as_array(self);
    obj_array_grow(obj_array);
    obj_t* result = obj_array_write(self, obj_array->objs_fill, obj);
    ++obj_array->objs_fill;
    return result;
}

void obj_array_push_array(obj_t* self, obj_t* other) {
    obj_array_t* obj_array = obj_as_array(self);
    obj_array_t* obj_array_other = obj_as_array(self);
    const size_t desired_size = obj_array->objs_fill + obj_array_other->objs_fill;
    if (obj_array->objs_capacity < desired_size) {
        // grow to the next power of 2
        size_t new_size = obj_array->objs_capacity ? obj_array->objs_capacity : 1;
        while (new_size < desired_size) {
            new_size *= 2;
        }
        obj_array_change_size(obj_array, new_size);
    }
    assert(desired_size <= obj_array->objs_capacity);
    memcpy(obj_array->objs + obj_array->objs_fill, obj_array_other->objs, obj_array_other->objs_fill * sizeof(*obj_array->objs));
    obj_array->objs_fill += obj_array_other->objs_fill;
}

obj_t* obj_array_pop(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    if (obj_array->objs_fill == 0) {
        throw(obj_string_new_cstr("empty array"), self);
    }
    --obj_array->objs_fill;
    obj_array_shrink(obj_array);
}

void obj_array_clear(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    obj_array->objs_fill = 0;
    obj_array_change_size(obj_array, 16);
}

size_t obj_array_size(obj_t* self) {
    obj_array_t* obj_array = obj_as_array(self);
    return obj_array->objs_fill;
}

obj_t* obj_array_read(obj_t* self, size_t index) {
    obj_array_t* obj_array = obj_as_array(self);
    if (obj_array->objs_fill <= index) {
        throw(obj_string_new_cstr("index out of bounds"), self, obj_i32_new(index));
    }
    return obj_array->objs[index];
}

obj_t* obj_array_write(obj_t* self, size_t index, obj_t* obj) {
    obj_array_t* obj_array = obj_as_array(self);
    if (obj_array->objs_fill < index) {
        throw(obj_string_new_cstr("index out of bounds"), self, obj, obj_i32_new(index));
    }
    obj_array->objs[index] = obj;
    return obj;
}
