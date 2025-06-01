#include "universe.h"

typedef obj_t* obj_array_element_t;

static double obj_array_load_factor(const obj_array_t* self);
static void obj_array_change_size(obj_array_t* self, size_t new_size);
static void obj_array_grow(obj_array_t* self);
static void obj_array_shrink(obj_array_t* self);

static double obj_array_load_factor(const obj_array_t* self) {
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

obj_array_t* obj_array_new() {
    obj_array_t* self = (obj_array_t*) malloc(sizeof(obj_array_t));
    obj_init((obj_t*) self, OBJ_TYPE_ARRAY);
    self->objs_capacity = 0;
    self->objs_fill = 0;
    self->objs = NULL;
    return self;
}

void obj_array_delete(obj_array_t* self) {
    if (self->objs) {
        free(self->objs);
    }
    free(self);
}

bool is_array(const obj_t* self) {
    return self->type == OBJ_TYPE_ARRAY;
}

obj_ffi_t* obj_array_to_ffi(const obj_array_t* self) {
    assert(0 && "todo: implement");
}

void obj_array_to_string(const obj_array_t* self, obj_string_t* str) {
    obj_string_push_cstr(str, "<%s ", obj_type_to_string(obj_get_type((obj_t*) self)));
    if (self->objs_fill) {
        obj_string_push_cstr(str, " ");
    }
    for (size_t i = 0; i < self->objs_fill; ++i) {
        obj_to_string(self->objs[i], str);
        if (i + 1 < self->objs_fill) {
            obj_string_push_cstr(str, ", ");
        }
    }
    obj_string_push_cstr(str, ">");
}

obj_array_t* obj_array_copy(const obj_array_t* self) {
    obj_array_t* copy = obj_array_new();
    for (size_t i = 0; i < self->objs_fill; ++i) {
        obj_array_push(copy, obj_copy(self->objs[i]));
    }
    return copy;
}

bool obj_array_equal(const obj_array_t* self, const obj_array_t* other) {
    if (self->objs_fill != other->objs_fill) {
        return false;
    }
    for (size_t i = 0; i < self->objs_fill; ++i) {
        if (!obj_equal(self->objs[i], other->objs[i])) {
            return false;
        }
    }
    return true;
}

bool obj_array_is_truthy(const obj_array_t* self) {
    return 0 < obj_array_size(self);
}


size_t obj_array_hash(const obj_array_t* self) {
    assert(0 && "todo: implement");
}

obj_t* obj_array_eval(const obj_array_t* self, obj_env_t* env) {
    return (obj_t*) self;
}

obj_t* obj_array_apply(const obj_array_t* self, obj_t* args, obj_env_t* env) {
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type((obj_t*) self))), (obj_t*) self);
}

obj_t* obj_array_push(obj_array_t* self, obj_t* obj) {
    obj_array_grow(self);
    obj_t* result = obj_array_write(self, self->objs_fill, obj);
    ++self->objs_fill;
    return result;
}

void obj_array_push_array(obj_array_t* self, const obj_array_t* other) {
    const size_t desired_size = self->objs_fill + other->objs_fill;
    if (self->objs_capacity < desired_size) {
        // grow to the next power of 2
        size_t new_size = self->objs_capacity ? self->objs_capacity : 1;
        while (new_size < desired_size) {
            new_size *= 2;
        }
        obj_array_change_size(self, new_size);
    }
    assert(desired_size <= self->objs_capacity);
    memcpy(self->objs + self->objs_fill, other->objs, other->objs_fill * sizeof(*self->objs));
    self->objs_fill += other->objs_fill;
}

obj_t* obj_array_pop(obj_array_t* self) {
    if (self->objs_fill == 0) {
        throw(obj_string_new_cstr("empty array"), self);
    }
    --self->objs_fill;
    obj_array_shrink(self);
}

void obj_array_clear(obj_array_t* self) {
    self->objs_fill = 0;
    obj_array_change_size(self, 16);
}

size_t obj_array_size(const obj_array_t* self) {
    return self->objs_fill;
}

obj_t* obj_array_read(const obj_array_t* self, size_t index) {
    if (self->objs_fill <= index) {
        throw(obj_string_new_cstr("index out of bounds"), self, obj_u32_new(index));
    }
    return self->objs[index];
}

obj_t* obj_array_write(obj_array_t* self, size_t index, obj_t* obj) {
    if (self->objs_fill < index) {
        throw(obj_string_new_cstr("index out of bounds"), self, obj, obj_u32_new(index));
    }
    self->objs[index] = obj;
    return obj;
}
