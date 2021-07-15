#include "set.h"

#include <assert.h>

#include "type.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

struct set_elem {
  cmp_t cmp;
  byte_t elem[1];
};

int set_cmp(const void *lhs, const void *rhs) {
  const struct set_elem *l = lhs, *r = rhs;
  assert(l->cmp == r->cmp);
  return l->cmp(&l->elem, &r->elem);
}
void set_set_dummy(struct set *self, const void *ptr) {
  struct buffer src, dst;
  size_t size = box_size(self->dummy);
  buffer_init(&src, (void *)ptr, size - sizeof(cmp_t));
  box_buffer(self->dummy, &dst);
  buffer_copy(&dst, sizeof(cmp_t), &src);
}

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
