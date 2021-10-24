#include "vec.h"

#include "array.h"
#include "type.h"
#include "util/util.h"

static index_t capacity_ceil(index_t cap) {
  enum { initial_capacity = 8 };
  index_t ceil = initial_capacity;
  while (ceil < cap) {
    ceil *= 2;
  }
  return ceil;
}
static void vec_expand(struct vec *self) {
  struct vec_array tmp;
  vec_array_init(&tmp, self->array.align);
  vec_array_alloc(&tmp, self->capacity);
  vec_array_insert(&tmp, self->array.ptr, self->array.count);
  UTIL_SWAP(struct vec_array, &tmp, &self->array);
  vec_array_free(&tmp);
}

struct vec *vec_new(void) {
  struct vec *self = util_malloc(sizeof(struct vec), 1);
  vec_array_init(&self->array, sizeof(void *));
  self->capacity = 0;
  return self;
}
void vec_delete(struct vec *self) {
  vec_array_free(&self->array);
  util_free(self);
}
void vec_reserve(struct vec *self, index_t count) {
  if (self->capacity < count) {
    self->capacity = capacity_ceil(count);
    vec_expand(self);
  }
}
index_t vec_capacity(struct vec *self) {
  return self->capacity;
}
index_t vec_length(struct vec *self) {
  return self->array.count;
}
void *vec_at(struct vec *self, index_t index) {
  return *(void **)vec_array_at(&self->array, index);
}
void *vec_top(struct vec *self) {
  return vec_at(self, -1);
}
void vec_push(struct vec *self, void *ptr) {
  vec_reserve(self, self->array.count + 1);
  vec_array_insert(&self->array, &ptr, 1);
}
void vec_pop(struct vec *self) {
  vec_array_remove(&self->array, 1);
}
void vec_clear(struct vec *self) {
  vec_array_remove(&self->array, self->array.count);
}
void vec_sort(struct vec *self, cmp_t cmp) {
  vec_array_sort(&self->array, cmp);
}
const void *vec_search(struct vec *self, const void *key, cmp_t cmp) {
  void **found = vec_array_search(&self->array, &key, cmp);
  return found ? *found : NULL;
}

void vec_map(struct vec *self, map_t map) {
  index_t index;
  assert(map);
  for (index = 0; index < vec_length(self); index++) {
    map(vec_at(self, index));
  }
}
