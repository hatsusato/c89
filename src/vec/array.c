#include "array.h"

#include "type.h"
#include "util/util.h"

void vec_array_init(struct vec_array *self, align_t align) {
  assert(0 < align);
  self->ptr = NULL;
  self->align = align;
  self->count = 0;
}
