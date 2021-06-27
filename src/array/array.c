#include "array.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "util/range.h"
#include "util/slice.h"

static void array_slide(struct array *self, const struct range *range) {
  void *src = array_at(self, range->begin);
  void *dst = array_at(self, range->end);
  if (src && dst) {
    size_t size = (array_length(self) - range->begin) * array_align(self);
    memmove(dst, src, size);
  }
  slice_resize(&self->slice, range_count(range));
}
static void array_copy(struct array *self, index_t index,
                       const struct slice *slice) {
  void *dst = array_at(self, index);
  const void *src = slice_at(slice, 0);
  if (src && dst) {
    memcpy(dst, src, slice_size(slice));
  }
}

void array_init(struct array *self, align_t align, struct buffer *buf) {
  assert(align > 0);
  self->align = align;
  if (buf) {
    self->buf = *buf;
    slice_init(&self->slice, align, buffer_at(buf, 0), 0);
  } else {
    buffer_init(&self->buf, NULL, 0);
    slice_init(&self->slice, align, NULL, 0);
  }
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
  assert(!ret || array_length(self) == 0);
  return ret;
}
align_t array_align(const struct array *self) {
  return self->align;
}
index_t array_length(const struct array *self) {
  return slice_length(&self->slice);
}
void *array_at(struct array *self, index_t index) {
  index_t length = array_length(self);
  index += (index < 0 ? length : 0);
  return (0 <= index && index < length)
             ? buffer_at(&self->buf, index * array_align(self))
             : NULL;
}
void array_insert(struct array *self, const struct range *range,
                  const struct slice *slice) {
  index_t index = range->begin;
  assert(range_is_valid(range));
  assert(index <= array_length(self));
  array_slide(self, range);
  array_copy(self, index, slice);
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
