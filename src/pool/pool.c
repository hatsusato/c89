#include "pool.h"

#include "type.h"
#include "util/util.h"
#include "vec/ptr.h"

struct pool *pool_new(void) {
  struct pool *self = util_malloc(sizeof(struct pool), 1);
  vec_ptr_init(&self->pool);
  return self;
}
void pool_delete(struct pool *self) {
  index_t i, length = vec_ptr_length(&self->pool);
  for (i = 0; i < length; i++) {
    void *elem = vec_ptr_at(&self->pool, i);
    util_free(elem);
  }
  vec_ptr_finish(&self->pool);
  util_free(self);
}
void *pool_alloc(struct pool *self, size_t size) {
  void *ptr = util_malloc(size, 1);
  vec_ptr_push(&self->pool, ptr);
  return ptr;
}
