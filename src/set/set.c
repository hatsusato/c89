#include "set.h"

#include <assert.h>

#include "type.h"
#include "util/box.h"
#include "util/buffer.h"
#include "util/util.h"
#include "vec/vec.h"

struct set_elem {
  cmp_t cmp;
  const void *ptr;
  byte_t elem[1];
};

static void set_elem_init(struct set_elem *self, struct set *set,
                          const void *ptr) {
  struct buffer buf;
  align_t align = set->align;
  self->cmp = set->cmp;
  self->ptr = util_malloc(align, 1);
  buffer_init(&buf, self->ptr, align);
  buffer_copy(&buf, 0, ptr, align);
}
static void set_elem_finish(void *ptr) {
  struct set_elem *self = ptr;
  util_free(self->ptr);
}
static int set_elem_cmp(const void *lhs, const void *rhs) {
  const struct set_elem *l = lhs, *r = rhs;
  assert(l->cmp == r->cmp);
  return l->cmp(l->ptr, r->ptr);
  ;
}

void set_init(struct set *self, align_t align, cmp_t cmp) {
  size_t size = sizeof(struct set_elem) + align;
  struct set_elem *elem;
  assert(cmp);
  vec_init(&self->vec, size);
  self->cmp = cmp;
  self->align = align;
  self->dummy = box_new(size, 1);
  elem = box_get(self->dummy);
  elem->cmp = cmp;
}
void set_finish(struct set *self) {
  vec_map(&self->vec, set_elem_finish);
  vec_finish(&self->vec);
  box_delete(self->dummy);
}
void set_insert(struct set *self, const void *ptr) {
  if (!set_search(self, ptr)) {
    struct set_elem elem;
    set_elem_init(&elem, self, ptr);
    vec_push(&self->vec, &elem);
    vec_sort(&self->vec, set_elem_cmp);
  }
}
const void *set_search(struct set *self, const void *key) {
  struct set_elem elem;
  const struct set_elem *found;
  elem.cmp = self->cmp;
  elem.ptr = key;
  found = vec_search(&self->vec, &elem, set_elem_cmp);
  return found ? found->ptr : NULL;
}
