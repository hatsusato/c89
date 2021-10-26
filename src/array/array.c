#include "array.h"

#include <stdlib.h>
#include <string.h>

#include "type.h"
#include "util/util.h"

void array_init(struct array *self, align_t align) {
  assert(0 < align);
  self->ptr = NULL;
  self->align = align;
  self->count = 0;
}
void array_finish(struct array *self) {
  util_free(self->ptr);
  self->ptr = NULL;
  self->count = 0;
}
void array_resize(struct array *self, index_t count) {
  struct array tmp;
  array_init(&tmp, self->align);
  tmp.ptr = util_malloc_array(self->align, count);
  array_insert(&tmp, self->ptr, UTIL_MIN(self->count, count));
  UTIL_SWAP(struct array, &tmp, self);
  array_finish(&tmp);
}
void array_set(struct array *self, void *ptr, index_t count) {
  assert(count == (ptr ? count : 0));
  self->ptr = ptr;
  self->count = count;
}
void *array_at(struct array *self, index_t index) {
  assert(self->ptr && -self->count <= index && index < self->count);
  index += index < 0 ? self->count : 0;
  return self->ptr + self->align * index;
}
void array_insert(struct array *self, const void *ptr, index_t count) {
  if (0 < count) {
    assert(self->ptr && ptr);
    memcpy(self->ptr + self->align * self->count, ptr, self->align * count);
    self->count += count;
  }
}
void array_remove(struct array *self, index_t count) {
  assert(count <= self->count);
  self->count -= count;
}
void array_sort(struct array *self, cmp_t cmp) {
  if (self->ptr) {
    qsort(self->ptr, self->count, self->align, cmp);
  }
}
void *array_search(struct array *self, const void *key, cmp_t cmp) {
  if (self->ptr) {
    return bsearch(key, self->ptr, self->count, self->align, cmp);
  }
  return NULL;
}
