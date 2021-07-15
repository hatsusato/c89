#include "set.h"

#include <assert.h>

#include "type.h"
#include "util/box.h"
#include "vec/vec.h"

struct set_elem {
  cmp_t cmp;
  byte_t elem[1];
};

void set_init(struct set *self, align_t align, cmp_t cmp) {
  size_t size = sizeof(cmp_t) + align;
  struct set_elem *elem;
  assert(cmp);
  vec_init(&self->vec, size);
  self->dummy = box_new(size, 1);
  elem = box_get(self->dummy);
  elem->cmp = cmp;
}
void set_finish(struct set *self) {
  vec_finish(&self->vec);
  box_delete(self->dummy);
}
