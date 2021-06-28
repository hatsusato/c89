#include "pool.h"

#include <stdlib.h>

#include "block.h"
#include "util/buffer.h"
#include "vec/ptr.h"
#include "vec/vec.h"

static void pool_small_free(void *self) {
  pool_block_free(self);
}
static void pool_small_push_block(struct pool *self) {
  struct pool_block block;
  pool_block_malloc(&block);
  vec_push(&self->small, &block);
}
static const void *pool_small_push(struct pool *self,
                                   const struct buffer *buf) {
  struct pool_block *block = vec_at(&self->small, -1);
  return pool_block_insert(block, buf);
}
static void pool_big_free(void *self) {
  free(self);
}
static const void *pool_big_push(struct pool *self, const struct buffer *src) {
  struct buffer dst;
  size_t size = buffer_size(src);
  void *ptr = buffer_malloc(&dst, size);
  buffer_memcpy(&dst, 0, src);
  vec_ptr_push(&self->big, ptr);
  return ptr;
}

void pool_malloc(struct pool *self) {
  vec_new(&self->small, sizeof(struct pool_block));
  pool_small_push_block(self);
  vec_ptr_new(&self->big);
}
void pool_free(struct pool *self) {
  vec_map(&self->small, pool_small_free);
  vec_delete(&self->small);
  vec_ptr_map(&self->big, pool_big_free);
  vec_ptr_delete(&self->big);
}
const void *pool_insert(struct pool *self, const struct buffer *buf) {
  const void *ptr = NULL;
  if (buffer_size(buf) < POOL_BLOCK_SIZE / 2) {
    ptr = pool_small_push(self, buf);
    if (!ptr) {
      pool_small_push_block(self);
      ptr = pool_small_push(self, buf);
    }
  } else {
    ptr = pool_big_push(self, buf);
  }
  return ptr;
}
