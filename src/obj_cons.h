#ifndef OBJ_CONS_H
# define OBJ_CONS_H

# include "obj.h"

struct obj_cons_t {
    obj_t base;
    obj_t* car;
    obj_t* cdr;
};

obj_cons_t* obj_cons_new(obj_t* car, obj_t* cdr);
void obj_cons_delete(obj_cons_t* self);

bool is_cons(const obj_t* self);
obj_ffi_t* obj_cons_to_ffi(const obj_cons_t* self);
void obj_cons_to_string(const obj_cons_t* self, obj_string_t* other);
obj_cons_t* obj_cons_copy(const obj_cons_t* self);
bool obj_cons_equal(const obj_cons_t* self, const obj_cons_t* other);
bool obj_cons_is_truthy(const obj_cons_t* self);
size_t obj_cons_hash(const obj_cons_t* self);
obj_t* obj_cons_eval(const obj_cons_t* self, obj_env_t* env);
obj_t* obj_cons_apply(const obj_cons_t* self, obj_t* args, obj_env_t* env);

obj_t* obj_cons_car(const obj_t* self);
obj_t* obj_cons_cdr(const obj_t* self);

obj_t* obj_cons_ref(const obj_t* self, size_t index);
obj_t* obj_cons_tail(const obj_t* self, size_t index);

obj_t* obj_cons_for_each(const obj_t* self, obj_t* (*fn)(const obj_t* obj, obj_env_t* env), obj_env_t* env);
obj_t* obj_cons_map(const obj_t* self, obj_t* (*fn)(const obj_t* obj, obj_env_t* env), obj_env_t* env);
obj_t* obj_cons_filter(const obj_t* self, bool (*predicate)(const obj_t* obj, obj_env_t* env), obj_env_t* env);
obj_t* obj_cons_fold_left(const obj_t* self, obj_t* (*combiner)(const obj_t* obj, obj_t* acc, obj_env_t* env), obj_t* acc, obj_env_t* env);
obj_t* obj_cons_fold_right(const obj_t* self, obj_t* (*combiner)(const obj_t* obj, obj_t* acc, obj_env_t* env), obj_t* acc, obj_env_t* env);

#endif // OBJ_CONS_H
