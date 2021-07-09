#include "pool.h"

#include "util/box.h"
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
const void *pool_insert(struct pool *self, struct box *box) {
  vec_ptr_push(&self->vec, box);
  return box_ptr(box);
}
