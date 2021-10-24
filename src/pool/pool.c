#include "pool.h"

#include "type.h"
#include "util/util.h"
#include "vec/ptr.h"

struct pool *pool_new(void) {
  struct pool *self = util_malloc(sizeof(struct pool), 1);
  self->pool = vec_new();
  return self;
}
void pool_delete(struct pool *self) {
  index_t i, length = vec_length(self->pool);
  for (i = 0; i < length; i++) {
    void *elem = vec_at(self->pool, i);
    util_free(elem);
  }
  vec_delete(self->pool);
  util_free(self);
}
void *pool_alloc(struct pool *self, size_t size) {
  void *ptr = util_malloc(size, 1);
  vec_push(self->pool, ptr);
  return ptr;
}
