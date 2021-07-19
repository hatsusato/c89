#include "pool.h"

#include "array/slice.h"
#include "type.h"
#include "util/box.h"
#include "util/box_type.h"
#include "util/util.h"
#include "vec/vec.h"

static void pool_finish(void *self) {
  box_finish(self);
}

struct pool *pool_new(void) {
  struct pool *self = util_malloc(sizeof(struct pool), 1);
  vec_init(&self->pool, sizeof(struct box));
  return self;
}
void pool_delete(struct pool *self) {
  slice_map(vec_slice(&self->pool), pool_finish);
  vec_finish(&self->pool);
  util_free(self);
}
void *pool_insert(struct pool *self, align_t align, index_t count) {
  struct box box;
  box_init(&box, align, count);
  vec_push(&self->pool, &box);
  return box_ptr(&box);
}
