#include "pool.h"

#include "type.h"
#include "util/util.h"
#include "vec/vec.h"

struct pool *pool_new(void) {
  struct pool *self = util_malloc(sizeof(struct pool));
  self->pool = vec_new();
  return self;
}
void pool_delete(struct pool *self) {
  vec_map(self->pool, util_free);
  vec_delete(self->pool);
  util_free(self);
}
void *pool_alloc(struct pool *self, size_t size) {
  void *ptr = util_malloc(size);
  vec_push(self->pool, ptr);
  return ptr;
}
