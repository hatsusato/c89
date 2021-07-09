#include "pool.h"

#include "util/buffer.h"
#include "vec/ptr.h"

static void pool_free(void *self) {
  box_delete(self);
}

void pool_new(struct pool *self) {
  vec_ptr_new(&self->vec);
}
void pool_delete(struct pool *self) {
  vec_ptr_map(&self->vec, pool_free);
  vec_ptr_delete(&self->vec);
}
const void *pool_insert(struct pool *self, const struct buffer *src) {
  struct box *box;
  struct buffer dst;
  box = box_new(buffer_size(src), 1);
  box_buffer(box, &dst);
  buffer_memcpy(&dst, 0, src);
  vec_ptr_push(&self->vec, box);
  return box_ptr(box);
}
