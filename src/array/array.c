#include "array.h"

void array_init(struct array *self, align_t align, struct buffer *buf) {
  self->align = align;
  self->buf = *buf;
  self->len = 0;
}
