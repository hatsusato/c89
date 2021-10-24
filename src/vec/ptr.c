#include "ptr.h"

#include "array.h"
#include "array/array.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

static index_t capacity_ceil(index_t cap) {
  enum { initial_capacity = 8 };
  index_t ceil = initial_capacity;
  while (ceil < cap) {
    ceil *= 2;
  }
  return ceil;
}
static void vec_ptr_expand(struct vec_ptr *self) {
  struct vec_array tmp;
  vec_array_init(&tmp, self->array.align);
  vec_array_alloc(&tmp, self->capacity);
  vec_array_insert(&tmp, self->array.ptr, self->array.count);
  UTIL_SWAP(struct vec_array, &tmp, &self->array);
  vec_array_free(&tmp);
}

struct vec_ptr *vec_ptr_new(void) {
  struct vec_ptr *self = util_malloc(sizeof(struct vec_ptr), 1);
  vec_init(&self->vec, sizeof(void *));
  vec_array_init(&self->array, sizeof(void *));
  self->capacity = 0;
  return self;
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_array_free(&self->array);
  vec_finish(&self->vec);
  util_free(self);
}
void vec_ptr_reserve(struct vec_ptr *self, index_t count) {
  vec_reserve(&self->vec, count);
  if (self->capacity < count) {
    self->capacity = capacity_ceil(count);
    vec_ptr_expand(self);
  }
}
index_t vec_ptr_capacity(struct vec_ptr *self) {
  return vec_capacity(&self->vec);
}
index_t vec_ptr_length(struct vec_ptr *self) {
  return self->array.count;
}
void *vec_ptr_at(struct vec_ptr *self, index_t index) {
  return *(void **)vec_array_at(&self->array, index);
}
void *vec_ptr_top(struct vec_ptr *self) {
  return vec_ptr_at(self, -1);
}
void vec_ptr_push(struct vec_ptr *self, void *ptr) {
  vec_push(&self->vec, &ptr);
  vec_ptr_reserve(self, self->array.count + 1);
  vec_array_insert(&self->array, &ptr, 1);
}
void vec_ptr_pop(struct vec_ptr *self) {
  vec_pop(&self->vec);
  vec_array_remove(&self->array, 1);
}
void vec_ptr_clear(struct vec_ptr *self) {
  vec_clear(&self->vec);
  vec_array_remove(&self->array, self->array.count);
}
void vec_ptr_map(struct vec_ptr *self, void (*map)(void *)) {
  index_t index;
  assert(map);
  for (index = 0; index < vec_ptr_length(self); index++) {
    map(vec_ptr_at(self, index));
  }
}
void vec_ptr_sort(struct vec_ptr *self, cmp_t cmp) {
  struct array *array = vec_get_array(&self->vec);
  array_sort(array, cmp);
  vec_array_sort(&self->array, cmp);
}
const void *vec_ptr_search(struct vec_ptr *self, const void *key, cmp_t cmp) {
  struct array *array = vec_get_array(&self->vec);
  void **found = array_search(array, &key, cmp);
  found = vec_array_search(&self->array, &key, cmp);
  return found ? *found : NULL;
}
