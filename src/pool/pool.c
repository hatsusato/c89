#include "pool.h"

void pool_malloc(struct pool *self, size_t size) {
  buffer_malloc(&self->buf, size);
  self->offset = 0;
}
void pool_free(struct pool *self) {
  buffer_free(&self->buf);
  self->offset = 0;
}
const void *pool_insert(struct pool *self, const struct buffer *buf) {
  const void *ptr = NULL;
  if (buffer_size(buf) + self->offset <= buffer_size(&self->buf)) {
    ptr = buffer_at(&self->buf, self->offset);
    buffer_memcpy(&self->buf, self->offset, buf);
  }
  return ptr;
}
