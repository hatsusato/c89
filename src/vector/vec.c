#include "vec.h"

#include "span.h"
#include "utility/type.h"

static struct vec *vector_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec);
  return (struct vec *)buf.ptr;
}
static void vector_free(struct vec *self) {
  struct buffer buf;
  BUFFER_INIT(&buf, self);
  buffer_free(&buf);
}

align_t vector_aligned_size(size_t size) {
  enum { vec_align = 8 };
  return (size + vec_align - 1) / vec_align * vec_align;
}
void vec_alloc(struct vec *self, size_t count) {
  buffer_malloc(&self->buf, self->align * count);
  vector_span_init(&self->span, self->buf.ptr);
}
void vec_reset(struct vec *self) {
  buffer_free(&self->buf);
  vector_span_init(&self->span, NULL);
}
struct vec *vec_new(size_t size) {
  struct vec *self = vector_malloc();
  self->align = self->span.align = vector_aligned_size(size);
  vector_span_init(&self->span, NULL);
  buffer_init(&self->buf, NULL, 0);
  return self;
}
struct vec *vec_create(size_t size) {
  enum { vec_initial_count = 8 };
  struct vec *self = vec_new(size);
  vec_reserve(self, vec_initial_count, NULL);
  return self;
}
void vec_delete(struct vec *self) {
  vec_reset(self);
  vector_free(self);
}
void vec_reserve(struct vec *self, size_t count, struct buffer *buf) {
  if (count == 0) {
    count = 2 * vec_capacity(self);
  }
  if (count > vec_capacity(self)) {
    size_t len = vec_length(self);
    struct buffer old = self->buf;
    vec_alloc(self, count);
    vector_span_push_back(&self->span, len, &old);
    if (buf) {
      *buf = old;
    } else {
      buffer_free(&old);
    }
  }
}
size_t vec_capacity(const struct vec *self) {
  return self->buf.size / self->align;
}
size_t vec_length(const struct vec *self) {
  return vector_span_length(&self->span);
}
bool_t vec_empty(const struct vec *self) {
  return vec_length(self) == 0;
}
bool_t vec_full(const struct vec *self) {
  return vec_length(self) == vec_capacity(self);
}
void *vec_begin(struct vec *self) {
  return self->span.begin;
}
void *vec_end(struct vec *self) {
  return self->span.end;
}
void *vec_at(struct vec *self, index_t i) {
  return vector_span_at(&self->span, i);
}
void vec_push(struct vec *self, const struct buffer *buf) {
  if (!vec_full(self)) {
    vector_span_push_back(&self->span, 1, buf);
  }
}
void vec_pop(struct vec *self, struct buffer *buf) {
  if (!vec_empty(self)) {
    vector_span_pop_back(&self->span, 1, buf);
  }
}
void vec_clear(struct vec *self) {
  vector_span_pop_back(&self->span, vec_length(self), NULL);
}
