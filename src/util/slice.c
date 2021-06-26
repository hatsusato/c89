#include "slice.h"

#include <assert.h>

#include "buffer.h"
#include "range.h"

void slice_init(struct slice *self, align_t align) {
  self->align = align;
  self->ptr = NULL;
  self->len = 0;
}
void slice_set(struct slice *self, const struct buffer *buf) {
  self->ptr = buffer_at(buf, 0);
  self->len = buffer_size(buf) / self->align;
}
void slice_slice(struct slice *self, const struct range *range) {
  assert(range_is_valid(range));
  assert(range->end <= self->len);
  self->ptr += range->begin;
  self->len = range_count(range);
}
bool_t slice_is_null(const struct slice *self) {
  assert(self->ptr || self->len == 0);
  return !self->ptr;
}
size_t slice_size(const struct slice *self) {
  return self->len * self->align;
}
const void *slice_at(const struct slice *self, index_t index) {
  assert(0 <= index);
  return (index < self->len) ? self->ptr + index * self->align : NULL;
}
