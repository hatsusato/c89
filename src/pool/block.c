#include "block.h"

#include "util/buffer.h"

void pool_block_new(struct pool_block *self) {
  box_new(&self->box, POOL_BLOCK_SIZE);
  self->offset = 0;
}
void pool_block_delete(struct pool_block *self) {
  box_delete(&self->box);
  self->offset = 0;
}
const void *pool_block_insert(struct pool_block *self,
                              const struct buffer *src) {
  struct buffer dst;
  const void *ptr = NULL;
  size_t offset = self->offset;
  box_buffer(&self->box, &dst);
  if (buffer_size(src) + offset <= buffer_size(&dst)) {
    buffer_memcpy(&dst, offset, src);
    ptr = buffer_at(&dst, offset);
    self->offset = offset + buffer_size(src);
  }
  return ptr;
}
