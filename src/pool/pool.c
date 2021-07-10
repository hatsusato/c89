#include "pool.h"

#include "type.h"
#include "util/box.h"
#include "vec/ptr.h"

static void pool_free(void *self) {
  box_delete(self);
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
