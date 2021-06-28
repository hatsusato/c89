#include "pool.h"

#include <stdlib.h>

#include "block.h"
#include "vec/ptr.h"
#include "vec/vec.h"

static void pool_small_free(void *self) {
  pool_block_free(self);
}
static void pool_big_free(void *self) {
  free(self);
}

void pool_malloc(struct pool *self, size_t size) {
  struct pool_block block;
  buffer_malloc(&self->buf, size);
  self->offset = 0;
  vec_new(&self->small, sizeof(struct pool_block));
  pool_block_malloc(&block);
  vec_push(&self->small, &block);
  vec_ptr_new(&self->big);
}
void pool_free(struct pool *self) {
  buffer_free(&self->buf);
  self->offset = 0;
  vec_map(&self->small, pool_small_free);
  vec_delete(&self->small);
  vec_ptr_map(&self->big, pool_big_free);
  vec_ptr_delete(&self->big);
}
const void *pool_insert(struct pool *self, const struct buffer *buf) {
  const void *ptr = NULL;
  if (buffer_size(buf) + self->offset <= buffer_size(&self->buf)) {
    ptr = buffer_at(&self->buf, self->offset);
    buffer_memcpy(&self->buf, self->offset, buf);
  }
  return ptr;
}
