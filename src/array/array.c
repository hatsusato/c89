#include "array.h"

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
