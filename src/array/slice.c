#include "slice.h"

#include <assert.h>

#include "type.h"
#include "util/buffer.h"

bool_t slice_is_valid(const struct slice *self) {
  return (self->align > 0 && (self->ptr || self->len == 0) && self->len >= 0);
}

void slice_init(struct slice *self, align_t align, const void *ptr,
                index_t len) {
  self->align = align;
  self->ptr = ptr;
  self->len = len;
  assert(slice_is_valid(self));
}
void slice_resize(struct slice *self, index_t count) {
  self->len += count;
  assert(slice_is_valid(self));
}
align_t slice_align(const struct slice *self) {
  return self->align;
}
index_t slice_length(const struct slice *self) {
  return self->len;
}
const void *slice_at(const struct slice *self, index_t index) {
  if (index < 0) {
    index += self->len;
  }
  if (0 <= index && index < self->len) {
    assert(self->ptr);
    return self->ptr + index * self->align;
  } else {
    return NULL;
  }
}
void slice_map(const struct slice *self, void (*map)(const void *)) {
  index_t index;
  assert(map);
  for (index = 0; index < slice_length(self); index++) {
    map(slice_at(self, index));
  }
}
