#include "array.h"

#include <assert.h>
#include <stdlib.h>

#include "util/range.h"
#include "util/slice.h"

static void array_slide(struct array *self, const struct range *range) {
  align_t align = array_align(self);
  size_t size = (array_length(self) - range->begin) * align;
  buffer_slide(&self->buf, range->begin * align, range->end * align, size);
  self->len += range_count(range);
}

void array_init(struct array *self, align_t align, struct buffer *buf) {
  assert(align > 0);
  self->align = align;
  if (buf) {
    self->buf = *buf;
  } else {
    buffer_init(&self->buf, NULL, 0);
  }
  self->len = 0;
}
void array_get(struct array *self, struct buffer *buf) {
  *buf = self->buf;
}
void array_slice(struct array *self, struct slice *slice) {
  index_t length = array_length(self);
  void *ptr = length > 0 ? array_at(self, 0) : NULL;
  slice_init(slice, array_align(self), ptr, length);
}
bool_t array_is_null(const struct array *self) {
  bool_t ret = buffer_is_null(&self->buf);
  assert(!ret || self->len == 0);
  return ret;
}
align_t array_align(const struct array *self) {
  return self->align;
}
index_t array_capacity(const struct array *self) {
  return buffer_size(&self->buf) / array_align(self);
}
index_t array_length(const struct array *self) {
  return self->len;
}
void *array_at(struct array *self, index_t index) {
  index_t length = array_length(self);
  index += (index < 0 ? length : 0);
  assert(0 <= index && index < length);
  return buffer_at(&self->buf, index * array_align(self));
}
void array_insert(struct array *self, const struct range *range,
                  const struct slice *slice) {
  struct buffer dst = self->buf, src;
  align_t align = array_align(self);
  index_t index = range->begin;
  size_t size = range_count(range) * align;
  assert(range_is_valid(range));
  assert(index <= array_length(self));
  assert(size <= slice_size(slice));
  array_slide(self, range);
  buffer_slice(&dst, index * align, size);
  buffer_init(&src, (void *)slice_at(slice, 0), slice_size(slice));
  buffer_memcpy(&dst, &src);
}
void array_remove(struct array *self, const struct range *range) {
  struct range inv;
  assert(range_is_valid(range));
  assert(range->end <= array_length(self));
  inv.begin = range->end;
  inv.end = range->begin;
  array_slide(self, &inv);
}
void array_push(struct array *self, const struct slice *slice) {
  struct range range;
  range_init(&range, array_length(self), 1);
  array_insert(self, &range, slice);
}
void array_pop(struct array *self) {
  struct range range;
  range_init(&range, array_length(self) - 1, 1);
  array_remove(self, &range);
}
void array_clear(struct array *self) {
  struct range range;
  range_init(&range, 0, array_length(self));
  array_remove(self, &range);
}
void array_sort(struct array *self, cmp_t cmp) {
  qsort(array_at(self, 0), array_length(self), array_align(self), cmp);
}
void *array_search(const struct array *self, const void *key, cmp_t cmp) {
  void *ptr = array_at((struct array *)self, 0);
  return bsearch(key, ptr, array_length(self), array_align(self), cmp);
}
void array_map(struct array *self, void (*map)(void *)) {
  index_t index;
  for (index = 0; index < array_length(self); index++) {
    map(array_at(self, index));
  }
}
