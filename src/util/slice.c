#include "slice.h"

#include <assert.h>

#include "buffer.h"

void slice_init(struct slice *self, align_t align) {
  self->align = align;
  self->ptr = NULL;
  self->len = 0;
}
void slice_set(struct slice *self, const struct buffer *buf) {
  self->ptr = buffer_at(buf, 0);
  self->len = buffer_size(buf) / self->align;
}
size_t slice_size(const struct slice *self) {
  return self->len * self->align;
}
const void *slice_at(const struct slice *self, index_t index) {
  assert(0 <= index && index < self->len);
  return self->ptr + index * self->align;
}
