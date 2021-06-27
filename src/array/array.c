#include "array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void array_slide(struct array *self, index_t from, index_t to) {
  const void *src = array_at(self, from);
  void *dst = array_at(self, to);
  if (src && dst) {
    size_t size = (array_length(self) - from) * array_align(self);
    memmove(dst, src, size);
  }
  slice_resize(&self->slice, to - from);
}
static void array_copy(struct array *self, index_t index,
                       const struct slice *slice) {
  const void *src = slice_at(slice, 0);
  void *dst = array_at(self, index);
  if (src && dst) {
    memcpy(dst, src, slice_size(slice));
  }
}

void array_init(struct array *self, align_t align, void *ptr) {
  slice_init(&self->slice, align, ptr, 0);
}
const struct slice *array_slice(const struct array *self) {
  return &self->slice;
}
align_t array_align(const struct array *self) {
  return slice_align(&self->slice);
}
index_t array_length(const struct array *self) {
  return slice_length(&self->slice);
}
void *array_at(struct array *self, index_t index) {
  return (void *)slice_at(&self->slice, index);
}
void array_insert(struct array *self, index_t offset,
                  const struct slice *slice) {
  assert(0 <= offset && offset <= array_length(self));
  array_slide(self, offset, offset + slice_length(slice));
  array_copy(self, offset, slice);
}
void array_remove(struct array *self, index_t offset, index_t length) {
  index_t from = offset + length, to = offset;
  assert(0 <= offset && 0 <= length && from <= array_length(self));
  array_slide(self, from, to);
}
void array_sort(struct array *self, cmp_t cmp) {
  void *ptr = array_at(self, 0);
  if (ptr) {
    qsort(ptr, array_length(self), array_align(self), cmp);
  }
}
void *array_search(const struct array *self, const void *key, cmp_t cmp) {
  void *ptr = array_at((struct array *)self, 0);
  return bsearch(key, ptr, array_length(self), array_align(self), cmp);
}
