#include "block.h"

void pool_block_new(struct pool_block *self) {
  buffer_malloc(&self->buf, POOL_BLOCK_SIZE);
  self->offset = 0;
}
void pool_block_delete(struct pool_block *self) {
  buffer_free(&self->buf);
  self->offset = 0;
}
const void *pool_block_insert(struct pool_block *self,
                              const struct buffer *buf) {
  const void *ptr = NULL;
  size_t size = buffer_size(buf);
  if (self->offset + size <= buffer_size(&self->buf)) {
    buffer_memcpy(&self->buf, self->offset, buf);
    ptr = buffer_at(&self->buf, self->offset);
    self->offset += size;
  }
  return ptr;
}
