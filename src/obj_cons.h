#ifndef OBJ_CONS_H
# define OBJ_CONS_H

# include "obj.h"

struct obj_cons_t {
    obj_t base;
    obj_t* car;
    obj_t* cdr;
};

obj_t* obj_cons_new(obj_t* car, obj_t* cdr);
void obj_cons_delete(obj_t* self);

bool is_cons(obj_t* self);
obj_cons_t* obj_as_cons(obj_t* self);
ffi_type* obj_cons_to_ffi(obj_t* self);
void obj_cons_to_string(obj_t* self, obj_t* string);
obj_t* obj_cons_copy(obj_t* self);
bool obj_cons_is_equal(obj_t* self, obj_t* other);
bool obj_cons_is_truthy(obj_t* self);
size_t obj_cons_hash(obj_t* self);
obj_t* obj_cons_eval(obj_t* self, obj_t* env);
obj_t* obj_cons_apply(obj_t* self, obj_t* args, obj_t* env);

obj_t* obj_cons_car(obj_t* self);
obj_t* obj_cons_cdr(obj_t* self);

obj_t* obj_cons_ref(obj_t* self, size_t index);
obj_t* obj_cons_tail(obj_t* self, size_t index);

obj_t* obj_cons_for_each(obj_t* self, obj_t* (*fn)(obj_t* obj, obj_t* env), obj_t* env);
obj_t* obj_cons_map(obj_t* self, obj_t* (*fn)(obj_t* obj, obj_t* env), obj_t* env);
obj_t* obj_cons_filter(obj_t* self, bool (*predicate)(obj_t* obj, obj_t* env), obj_t* env);
obj_t* obj_cons_fold_left(obj_t* self, obj_t* (*combiner)(obj_t* obj, obj_t* acc, obj_t* env), obj_t* acc, obj_t* env);
obj_t* obj_cons_fold_right(obj_t* self, obj_t* (*combiner)(obj_t* obj, obj_t* acc, obj_t* env), obj_t* acc, obj_t* env);

#endif // OBJ_CONS_H
