#include "slice.h"

#include <assert.h>

size_t slice_size(const struct slice *self) {
  return self->len * self->align;
}
const void *slice_at(const struct slice *self, index_t index) {
  assert(0 <= index && index < self->len);
  return self->ptr + index * self->align;
}
