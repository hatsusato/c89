#include "slice.h"

#include <assert.h>

#include "range.h"

void slice_init(struct slice *self, align_t align, const void *ptr,
                index_t len) {
  assert(0 <= len);
  self->align = align;
  self->ptr = ptr;
  self->len = len;
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
