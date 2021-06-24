#include "array.h"

#include <assert.h>

void array_init(struct array *self, align_t align, struct buffer *buf) {
  self->align = align;
  self->buf = *buf;
  self->len = 0;
}
index_t array_capacity(const struct array *self) {
  return self->buf.size / self->align;
}
index_t array_length(const struct array *self) {
  return self->len;
}
void *array_at(struct array *self, index_t index) {
  assert(0 <= index && index < array_length(self));
  return self->buf.ptr + index * self->align;
}
