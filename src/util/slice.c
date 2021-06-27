#include "slice.h"

#include <assert.h>

#include "range.h"

static bool_t slice_is_valid(const struct slice *self) {
  return (self->align > 0 && (self->ptr || self->len == 0) && self->len >= 0);
}

void slice_init(struct slice *self, align_t align, const void *ptr,
                index_t len) {
  self->align = align;
  self->ptr = ptr;
  self->len = len;
  assert(slice_is_valid(self));
}
void slice_slice(struct slice *self, const struct range *range) {
  assert(range_is_valid(range));
  assert(range->end <= self->len);
  assert(self->ptr);
  self->ptr += range->begin;
  self->len = range_count(range);
  assert(slice_is_valid(self));
}
void slice_resize(struct slice *self, index_t count) {
  self->len += count;
  assert(slice_is_valid(self));
}
bool_t slice_is_null(const struct slice *self) {
  return !self->ptr;
}
index_t slice_length(const struct slice *self) {
  return self->len;
}
size_t slice_size(const struct slice *self) {
  return self->len * self->align;
}
const void *slice_at(const struct slice *self, index_t index) {
  if (index < 0) {
    index += self->len;
  }
  if (0 <= index && index < self->len) {
    assert(self->ptr);
    return self->ptr + index * self->align;
  } else {
    return NULL;
  }
}
