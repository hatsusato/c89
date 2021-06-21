#include "vec.h"

#include "span.h"
#include "utility/buffer.h"
#include "utility/type.h"

static align_t vector_aligned_size(size_t size) {
  enum { vector_align = 8 };
  size += vector_align - 1;
  size /= vector_align;
  size *= vector_align;
  return size;
}
static align_t vector_align(const struct vec *self) {
  return self->span.align;
}
static void vector_malloc_data(struct vec *self, size_t count) {
  struct buffer buf;
  buffer_malloc(&buf, vector_align(self) * count);
  vec_init(self, &buf);
}
static void vector_free_data(struct vec *self) {
  struct buffer buf;
  buffer_init(&buf, self->span.begin, self->capacity);
  buffer_free(&buf);
}
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
static void vector_init_buffer(struct vec *self, struct buffer *buf) {
  buffer_init(buf, self->span.begin, self->capacity);
}

void vec_init(struct vec *self, struct buffer *buf) {
  vector_span_init(&self->span, buf->ptr, 0);
  self->capacity = buf->size;
}
void vec_init_malloc(struct vec *self, size_t count) {
  struct buffer buf;
  buffer_malloc(&buf, vector_align(self) * count);
  vec_init(self, &buf);
}
struct vec *vec_new(size_t size) {
  struct vec *self = vector_malloc();
  vector_span_init(&self->span, NULL, vector_aligned_size(size));
  return self;
}
struct vec *vec_create(size_t size) {
  enum { vec_initial_count = 8 };
  struct vec *self = vec_new(size);
  vector_malloc_data(self, vec_initial_count);
  return self;
}
void vec_delete(struct vec *self) {
  vector_free_data(self);
  vector_free(self);
}
void vec_reserve(struct vec *self, size_t count, struct buffer *buf) {
  if (count == 0) {
    count = 2 * vec_capacity(self);
  }
  if (count > vec_capacity(self)) {
    struct buffer dst, src;
    align_t align = vector_align(self);
    size_t cap = align * count;
    size_t len = vec_length(self);
    buffer_malloc(&dst, cap);
    vector_init_buffer(self, &src);
    if (!vec_empty(self)) {
      src.ptr = self->span.begin;
      src.size = align * len;
      buffer_memcpy(&dst, &src);
    }
    self->span.begin = dst.ptr;
    self->span.end = dst.ptr + align * len;
    self->capacity = cap;
    if (buf) {
      *buf = src;
      buf = NULL;
    } else {
      buf = &src;
    }
    buffer_free(buf);
  }
}
size_t vec_capacity(const struct vec *self) {
  return self->capacity / vector_align(self);
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
void vec_copy(struct vec *self, const struct vec *other) {
  struct buffer dst, src;
  vector_init_buffer(self, &dst);
  vector_init_buffer((struct vec *)other, &src);
  buffer_memcpy(&dst, &src);
}
void vec_clear(struct vec *self) {
  self->span.end = self->span.begin;
}
