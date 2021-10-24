#include "array.h"

#include <stdlib.h>

#include "type.h"
#include "util/util.h"

void vec_array_init(struct vec_array *self, align_t align) {
  assert(0 < align);
  self->ptr = NULL;
  self->align = align;
  self->count = 0;
}
void vec_array_set(struct vec_array *self, void *ptr, index_t count) {
  assert(count == (ptr ? count : 0));
  self->ptr = ptr;
  self->count = count;
}
void *vec_array_at(struct vec_array *self, index_t index) {
  assert(self->ptr && 0 <= index && index < self->count);
  return self->ptr + self->align * index;
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
