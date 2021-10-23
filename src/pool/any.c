#include "any.h"

#include "type.h"
#include "util/util.h"
#include "vec/ptr.h"

struct pool_any *pool_any_new(void) {
  struct pool_any *self = util_malloc(sizeof(struct pool_any), 1);
  vec_ptr_init(&self->pool);
  return self;
}
void pool_any_delete(struct pool_any *self) {
  index_t i, length = vec_ptr_length(&self->pool);
  for (i = 0; i < length; i++) {
    void *elem = vec_ptr_at(&self->pool, i);
    util_free(elem);
  }
  util_free(self);
}
