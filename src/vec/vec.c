#include "vec.h"

#include <assert.h>

#include "type.h"
#include "util/range.h"
#include "util/util.h"

static struct array *vec_inner(const struct vec *self) {
  return (struct array *)&self->array;
}
static align_t vec_align(const struct vec *self) {
  return array_align(vec_inner(self));
}

struct vec *vec_new(align_t align) {
  struct buffer buf;
  struct vec *self = BUFFER_MALLOC(&buf, struct vec);
  vec_init(self, align);
  return self;
}
void vec_delete(struct vec *self) {
  struct buffer buf;
  vec_free(self);
  BUFFER_INIT(&buf, self);
  buffer_free(&buf);
}
void vec_init(struct vec *self, align_t align) {
  assert(align > 0);
  array_init(vec_inner(self), align);
}
void vec_malloc(struct vec *self, index_t count) {
  assert(array_is_null(vec_inner(self)));
  array_malloc(vec_inner(self), count);
}
void vec_free(struct vec *self) {
  array_free(vec_inner(self));
}
void vec_reserve(struct vec *self, index_t count) {
  struct vec tmp;
  struct buffer buf;
  index_t cap = vec_capacity(self);
  assert(0 <= count);
  if (count <= cap) {
    return;
  }
  vec_init(&tmp, vec_align(self));
  vec_malloc(&tmp, UTIL_MAX(count, 2 * cap));
  array_get(vec_inner(self), &buf);
  vec_insert(&tmp, 0, vec_length(self), &buf);
  UTIL_SWAP(struct vec, self, &tmp);
  vec_free(&tmp);
}
index_t vec_capacity(const struct vec *self) {
  return array_capacity(vec_inner(self));
}
index_t vec_length(const struct vec *self) {
  return array_length(vec_inner(self));
}
void *vec_at(struct vec *self, index_t index) {
  return array_at(vec_inner(self), index);
}
void vec_insert(struct vec *self, index_t index, index_t count,
                const struct buffer *buf) {
  index_t len = vec_length(self);
  struct range range;
  assert(0 <= index && 0 <= count);
  assert(index <= len);
  assert(count * vec_align(self) <= buf->size);
  vec_reserve(self, len + count);
  range_init(&range, index, count);
  array_insert(vec_inner(self), &range, buf);
}
void vec_remove(struct vec *self, index_t index, index_t count) {
  struct range range;
  assert(0 <= index && 0 <= count);
  assert(index + count <= vec_length(self));
  range_init(&range, index, count);
  array_remove(vec_inner(self), &range);
}
void vec_clear(struct vec *self) {
  vec_remove(self, 0, vec_length(self));
}
