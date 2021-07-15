#include "set.h"

#include <assert.h>

#include "type.h"
#include "vec/vec.h"

void set_init(struct set *self, align_t size, cmp_t cmp) {
  assert(cmp);
  vec_init(&self->vec, sizeof(struct set *) + size);
  self->cmp = cmp;
}
void set_finish(struct set *self) {
  vec_finish(&self->vec);
}
