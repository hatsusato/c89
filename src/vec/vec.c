#include "vec.h"

#include <assert.h>

#include "type.h"
#include "util/buffer.h"
#include "util/slice.h"
#include "util/util.h"

static struct array *vec_inner(const struct vec *self) {
  return (struct array *)&self->array;
}
static align_t vec_align(const struct vec *self) {
  return array_align(vec_inner(self));
}

void vec_init(struct vec *self, align_t align) {
  assert(align > 0);
  array_init(vec_inner(self), align, NULL);
  self->capacity = 0;
}
void vec_malloc(struct vec *self, index_t len) {
  struct buffer buf;
  align_t align = vec_align(self);
  assert(!slice_ptr(array_slice(vec_inner(self))));
  assert(0 <= len);
  array_init(vec_inner(self), align, buffer_malloc(&buf, align * len));
  self->capacity = len;
}
void vec_free(struct vec *self) {
  struct buffer buf;
  void *ptr = (void *)slice_ptr(array_slice(vec_inner(self)));
  buffer_init(&buf, ptr, self->capacity);
  buffer_free(&buf);
  array_init(vec_inner(self), vec_align(self), NULL);
  self->capacity = 0;
}
static void vec_assign(struct vec *dst, const struct vec *src, index_t len) {
  vec_init(dst, vec_align(src));
  vec_malloc(dst, len);
  vec_insert(dst, 0, array_slice(vec_inner(src)));
}
void vec_reserve(struct vec *self, index_t len) {
  index_t cap = vec_capacity(self);
  assert(0 <= len);
  if (len > cap) {
    struct vec tmp;
    vec_assign(&tmp, self, UTIL_MAX(len, 2 * cap));
    UTIL_SWAP(struct vec, self, &tmp);
    vec_free(&tmp);
  }
}
index_t vec_capacity(const struct vec *self) {
  return self->capacity;
}
index_t vec_length(const struct vec *self) {
  return array_length(vec_inner(self));
}
const struct slice *vec_slice(const struct vec *self) {
  return array_slice(vec_inner(self));
}
void *vec_at(struct vec *self, index_t index) {
  return array_at(vec_inner(self), index);
}
void vec_insert(struct vec *self, index_t offset, const struct slice *slice) {
  vec_reserve(self, vec_length(self) + slice_length(slice));
  array_insert(vec_inner(self), offset, slice);
}
void vec_remove(struct vec *self, index_t offset, index_t length) {
  array_remove(vec_inner(self), offset, length);
}
void vec_push(struct vec *self, const void *ptr) {
  struct slice slice;
  slice_init(&slice, vec_align(self), ptr, 1);
  vec_insert(self, vec_length(self), &slice);
}
void vec_pop(struct vec *self) {
  vec_remove(self, vec_length(self) - 1, 1);
}
void vec_clear(struct vec *self) {
  vec_remove(self, 0, vec_length(self));
}
void vec_sort(struct vec *self, cmp_t cmp) {
  array_sort(vec_inner(self), cmp);
}
void *vec_search(const struct vec *self, const void *key, cmp_t cmp) {
  return array_search(vec_inner(self), key, cmp);
}
