#include "box.h"

#include <assert.h>
#include <stdlib.h>

#include "box_type.h"
#include "buffer.h"
#include "util.h"

void box_init(struct box *self, align_t align, index_t count) {
  self->size = count * align;
  self->ptr = util_malloc(align, count);
}
void box_finish(struct box *self) {
  util_free(self->ptr);
}
struct box *box_new(align_t align, index_t count) {
  size_t size = align * count;
  struct box *box = malloc(sizeof(size_t) + sizeof(const void *) + size);
  box->size = size;
  return box;
}
void box_delete(struct box *box) {
  free(box);
}
void box_buffer(struct box *box, struct buffer *buf) {
  buffer_init(buf, box_get(box), box_size(box));
}
void *box_get(const struct box *box) {
  const byte_t *ptr = box->data;
  return (void *)ptr;
}
void box_release(void *ptr) {
  byte_t *data = ptr;
  struct box *box = (void *)(data - sizeof(size_t) - sizeof(const void *));
  assert(box_get(box) == ptr);
  box_delete(box);
}
size_t box_size(const struct box *box) {
  return box->size;
}
