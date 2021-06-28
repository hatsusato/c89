#include "block.h"

void pool_block_malloc(struct pool_block *self) {
  enum { pool_block_size = 4096 };
  buffer_malloc(&self->buf, pool_block_size);
  self->offset = 0;
}
void pool_block_free(struct pool_block *self) {
  buffer_free(&self->buf);
  self->offset = 0;
}
