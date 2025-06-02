#include "universe.h"

obj_t* obj_pointer_new(void* ptr) {
    obj_pointer_t* self = (obj_pointer_t*) malloc(sizeof(obj_pointer_t));
    obj_init((obj_t*) self, OBJ_TYPE_POINTER);
    self->ptr = ptr;
    return (obj_t*) self;
}

void obj_pointer_delete(obj_t* self) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    free(self);
}

bool is_pointer(obj_t* self) {
    return self->type == OBJ_TYPE_POINTER;
}

obj_pointer_t* obj_as_pointer(obj_t* self) {
    if (!is_pointer(self)) {
        throw(obj_string_new_cstr("expected obj_pointer_t, got %s", obj_type_to_string(obj_get_type(self))), self);
    }
    return (obj_pointer_t*) self;
}

ffi_type* obj_pointer_to_ffi(obj_t* self) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    assert(0 && "todo: implement");
}

void obj_pointer_to_string(obj_t* self, obj_t* string) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    obj_string_push_cstr(string, "<%s %p>", obj_type_to_string(obj_get_type(self)), obj_pointer->ptr);
}

obj_t* obj_pointer_copy(obj_t* self) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    obj_t* copy = obj_pointer_new(obj_pointer->ptr);
    return copy;
}

bool obj_pointer_is_equal(obj_t* self, obj_t* other) {
    obj_pointer_t* pointer_self = obj_as_pointer(self);
    obj_pointer_t* pointer_other = obj_as_pointer(other);
    return pointer_self->ptr == pointer_other->ptr;
}

bool obj_pointer_is_truthy(obj_t* self) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    return obj_pointer->ptr != NULL;
}

size_t obj_pointer_hash(obj_t* self) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    assert(0 && "todo: implement");
}

obj_t* obj_pointer_eval(obj_t* self, obj_t* env) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    return self;
}

obj_t* obj_pointer_apply(obj_t* self, obj_t* args, obj_t* env) {
    obj_pointer_t* obj_pointer = obj_as_pointer(self);
    throw(obj_string_new_cstr("cannot apply %s", obj_type_to_string(obj_get_type(self))), self);
}
