#include "array.h"

#include <assert.h>
#include <stdlib.h>

#include "slice.h"
#include "type.h"
#include "util/buffer.h"
#include "util/util.h"

static struct slice *array_inner(struct array *self) {
  return &self->slice;
}
static void array_slide(struct array *self, index_t index, index_t count) {
  void *ptr = array_at(self, 0);
  if (ptr) {
    struct buffer buf;
    align_t align = array_align(self);
    index_t len = array_length(self);
    index_t max = len + UTIL_MAX(0, count);
    size_t from = index * align;
    size_t to = from + count * align;
    size_t offset = (len - index) * align;
    buffer_init(&buf, ptr, max * align);
    buffer_slide(&buf, from, to, offset);
  }
  slice_resize(array_inner(self), count);
}

void array_init(struct array *self, align_t align, void *ptr) {
  slice_init(array_inner(self), align, ptr, 0);
}
const struct slice *array_slice(const struct array *self) {
  return &self->slice;
}
align_t array_align(const struct array *self) {
  return slice_align(array_slice(self));
}
index_t array_length(const struct array *self) {
  return slice_length(array_slice(self));
}
void *array_at(struct array *self, index_t index) {
  return (void *)slice_at(array_inner(self), index);
}
void array_insert(struct array *self, index_t offset,
                  const struct slice *slice) {
  struct buffer src, dst;
  assert(0 <= offset && offset <= array_length(self));
  assert(array_align(self) == slice_align(slice));
  array_slide(self, offset, slice_length(slice));
  slice_buffer((struct slice *)slice, &src);
  slice_buffer((struct slice *)array_slice(self), &dst);
  buffer_copy(&dst, offset * array_align(self), &src);
}
void array_remove(struct array *self, index_t offset, index_t length) {
  assert(0 <= offset && 0 <= length);
  assert(offset + length <= array_length(self));
  array_slide(self, offset + length, -length);
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
