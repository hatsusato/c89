#include "set.h"

#include <assert.h>

#include "type.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

struct set_elem {
  cmp_t cmp;
  void *ptr;
  byte_t elem[1];
};

static int set_cmp(const void *lhs, const void *rhs) {
  const struct set_elem *l = lhs, *r = rhs;
  assert(l->cmp == r->cmp);
  return l->cmp(l->elem, r->elem);
}
static void set_set_dummy(struct set *self, const void *ptr) {
  struct buffer buf;
  box_buffer(self->dummy, &buf);
  buffer_copy(&buf, sizeof(cmp_t) + sizeof(void *), ptr, self->align);
}
static const void *set_get_dummy(struct set *self) {
  return box_get(self->dummy);
}

void set_init(struct set *self, align_t align, cmp_t cmp) {
  size_t size = sizeof(struct set_elem) + align;
  struct set_elem *elem;
  assert(cmp);
  vec_init(&self->vec, size);
  self->align = align;
  self->dummy = box_new(size, 1);
  elem = box_get(self->dummy);
  elem->cmp = cmp;
}
void set_finish(struct set *self) {
  vec_finish(&self->vec);
  box_delete(self->dummy);
}
void set_insert(struct set *self, const void *ptr) {
  if (!set_search(self, ptr)) {
    set_set_dummy(self, ptr);
    vec_push(&self->vec, set_get_dummy(self));
    vec_sort(&self->vec, set_cmp);
  }
}
const void *set_search(struct set *self, const void *key) {
  const struct set_elem *found;
  set_set_dummy(self, key);
  found = vec_search(&self->vec, set_get_dummy(self), set_cmp);
  return found ? found->elem : NULL;
}
