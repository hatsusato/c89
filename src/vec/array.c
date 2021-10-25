#include "array.h"

#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "util/util.h"

void vec_array_init(struct vec_array *self, align_t align) {
  assert(0 < align);
  self->ptr = NULL;
  self->align = align;
  self->count = 0;
}
void vec_array_alloc(struct vec_array *self, index_t count) {
  assert(!self->ptr && self->count == 0);
  self->ptr = util_malloc_array(self->align, count);
  self->count = 0;
}
void vec_array_free(struct vec_array *self) {
  util_free(self->ptr);
  self->ptr = NULL;
  self->count = 0;
}
void vec_array_set(struct vec_array *self, void *ptr, index_t count) {
  assert(count == (ptr ? count : 0));
  self->ptr = ptr;
  self->count = count;
}
void *vec_array_at(struct vec_array *self, index_t index) {
  assert(self->ptr && -self->count <= index && index < self->count);
  index += index < 0 ? self->count : 0;
  return self->ptr + self->align * index;
}
void vec_array_insert(struct vec_array *self, const void *ptr, index_t count) {
  if (0 < count) {
    assert(self->ptr && ptr);
    memcpy(self->ptr + self->align * self->count, ptr, self->align * count);
    self->count += count;
  }
}
void vec_array_remove(struct vec_array *self, index_t count) {
  assert(count <= self->count);
  self->count -= count;
}
void vec_array_sort(struct vec_array *self, cmp_t cmp) {
  if (self->ptr) {
    qsort(self->ptr, self->count, self->align, cmp);
  }
}
void *vec_array_search(struct vec_array *self, const void *key, cmp_t cmp) {
  if (self->ptr) {
    return bsearch(key, self->ptr, self->count, self->align, cmp);
  }
  return NULL;
}
