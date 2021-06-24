#include "array.h"

#include <assert.h>

void array_slide(struct array *self, index_t index, index_t count) {
  align_t align = array_align(self);
  index_t length = array_length(self);
  size_t from = index * align;
  size_t to = (index + count) * align;
  size_t size = (length - index) * align;
  assert(0 <= index && index <= length);
  buffer_slide(&self->buf, from, to, size);
  self->len += count;
}

void array_init(struct array *self, align_t align, struct buffer *buf) {
  self->align = align;
  self->buf = *buf;
  self->len = 0;
}
align_t array_align(const struct array *self) {
  return self->align;
}
index_t array_capacity(const struct array *self) {
  return self->buf.size / array_align(self);
}
index_t array_length(const struct array *self) {
  return self->len;
}
void *array_at(struct array *self, index_t index) {
  assert(0 <= index && index < array_length(self));
  return self->buf.ptr + index * array_align(self);
}
