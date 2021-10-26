#include "vec.h"

#include "array/array.h"
#include "type.h"
#include "util/util.h"

static index_t vec_capacity_ceil(index_t cap) {
  enum { initial_capacity = 8 };
  index_t ceil = initial_capacity;
  while (ceil < cap) {
    ceil *= 2;
  }
  return ceil;
}

struct vec *vec_new(void) {
  struct vec *self = util_malloc(sizeof(struct vec));
  array_init(&self->array, sizeof(struct vec_entry));
  self->capacity = 0;
  return self;
}
void vec_delete(struct vec *self) {
  array_finish(&self->array);
  util_free(self);
}
void vec_reserve(struct vec *self, index_t count) {
  if (self->capacity < count) {
    self->capacity = vec_capacity_ceil(count);
    array_resize(&self->array, self->capacity);
  }
}
index_t vec_capacity(struct vec *self) {
  return self->capacity;
}
index_t vec_length(struct vec *self) {
  return self->array.count;
}
void *vec_at(struct vec *self, index_t index) {
  struct vec_entry *entry = array_at(&self->array, index);
  return entry->ptr;
}
void *vec_top(struct vec *self) {
  return vec_at(self, -1);
}
void vec_push(struct vec *self, void *ptr) {
  struct vec_entry entry;
  vec_reserve(self, self->array.count + 1);
  entry.ptr = ptr;
  array_insert(&self->array, &entry, 1);
}
void vec_pop(struct vec *self) {
  array_remove(&self->array, 1);
}
void vec_clear(struct vec *self) {
  array_remove(&self->array, self->array.count);
}
void vec_sort(struct vec *self, cmp_t cmp) {
  array_sort(&self->array, cmp);
}
void *vec_search(struct vec *self, const void *key, cmp_t cmp) {
  struct vec_entry entry, *found;
  entry.ptr = (void *)key;
  found = array_search(&self->array, &entry, cmp);
  return found ? found->ptr : NULL;
}

void vec_map(struct vec *self, map_t map) {
  index_t index;
  assert(map);
  for (index = 0; index < vec_length(self); index++) {
    map(vec_at(self, index));
  }
}
