#include "pool.h"

#include "type.h"
#include "util/box.h"
#include "vec/ptr.h"

static void pool_free(void *self) {
  box_delete(self);
}

struct pool *pool_new(void) {
  struct box *box = box_new(sizeof(struct pool), 1);
  struct pool *self = box_get(box);
  pool_init(self);
  return self;
}
void pool_delete(struct pool *self) {
  pool_finish(self);
  box_release(self);
}
void pool_init(struct pool *self) {
  vec_ptr_init(&self->vec);
}
void pool_finish(struct pool *self) {
  vec_ptr_map(&self->vec, pool_free);
  vec_ptr_finish(&self->vec);
}
void *pool_insert(struct pool *self, struct box *box) {
  vec_ptr_push(&self->vec, box);
  return box_get(box);
}
