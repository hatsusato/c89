#include "pool.h"

#include "array/slice.h"
#include "type.h"
#include "util/box.h"
#include "util/box_type.h"
#include "util/util.h"
#include "vec/ptr.h"
#include "vec/vec.h"

static void pool_free(void *self) {
  box_delete(self);
}
static void pool_finish(const void *self) {
  box_finish((void *)self);
}

struct pool *pool_new(void) {
  struct pool *self = util_malloc(sizeof(struct pool), 1);
  vec_init(&self->pool, sizeof(struct box));
  vec_ptr_init(&self->vec);
  return self;
}
void pool_delete(struct pool *self) {
  slice_map(vec_slice(&self->pool), pool_finish);
  vec_finish(&self->pool);
  vec_ptr_map(&self->vec, pool_free);
  vec_ptr_finish(&self->vec);
  util_free(self);
}
void *pool_insert(struct pool *self, struct box *box) {
  vec_ptr_push(&self->vec, box);
  return box_get(box);
}
