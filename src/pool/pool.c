#include "pool.h"

#include <stdlib.h>

#include "util/buffer.h"
#include "vec/ptr.h"

static void pool_big_free(void *self) {
  free(self);
}
static const void *pool_big_push(struct pool *self, const struct buffer *src) {
  struct box box;
  struct buffer dst;
  box_new(&box, buffer_size(src));
  box_buffer(&box, &dst);
  buffer_memcpy(&dst, 0, src);
  vec_ptr_push(&self->big, box_ptr(&box));
  return box_ptr(&box);
}

void pool_new(struct pool *self) {
  vec_ptr_new(&self->big);
}
void pool_delete(struct pool *self) {
  vec_ptr_map(&self->big, pool_big_free);
  vec_ptr_delete(&self->big);
}
const void *pool_insert(struct pool *self, const struct buffer *buf) {
  return pool_big_push(self, buf);
}
