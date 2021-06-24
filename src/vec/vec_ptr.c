#include "vec_ptr.h"

#include "type.h"
#include "util/buffer.h"
#include "vec.h"

static struct vec_ptr *vec_ptr_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec_ptr);
  return (struct vec_ptr *)buf.ptr;
}
static void vec_ptr_free(struct vec_ptr *self) {
  struct buffer buf;
  BUFFER_INIT(&buf, self);
  buffer_free(&buf);
}
static void vec_ptr_destruct(struct vec_ptr *self, void *ptr) {
  if (self->dtor) {
    (self->dtor)(ptr);
  }
}

struct vec_ptr *vec_ptr_new(void (*dtor)(void *)) {
  enum { initial_count = 8 };
  struct vec_ptr *self = vec_ptr_malloc();
  vec_init(&self->vec, sizeof(void *));
  vec_malloc(&self->vec, initial_count);
  self->dtor = dtor;
  return self;
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_ptr_clear(self);
  vec_free(&self->vec);
  vec_ptr_free(self);
}
index_t vec_ptr_capacity(struct vec_ptr *self) {
  return vec_capacity(&self->vec);
}
index_t vec_ptr_length(struct vec_ptr *self) {
  return vec_length(&self->vec);
}
void *vec_ptr_at(struct vec_ptr *self, index_t index) {
  return *(void **)vec_at(&self->vec, index);
}
void vec_ptr_push(struct vec_ptr *self, void *ptr) {
  struct vec *vec = &self->vec;
  struct buffer buf;
  BUFFER_INIT(&buf, &ptr);
  vec_insert(vec, vec_length(vec), 1, &buf);
}
void vec_ptr_pop(struct vec_ptr *self) {
  void *ptr = vec_ptr_at(self, vec_ptr_length(self) - 1);
  vec_ptr_destruct(self, ptr);
  vec_remove(&self->vec, vec_length(&self->vec) - 1, 1);
}
void **vec_ptr_begin(struct vec_ptr *self) {
  return vec_begin(&self->vec);
}
void **vec_ptr_end(struct vec_ptr *self) {
  return vec_end(&self->vec);
}
void vec_ptr_clear(struct vec_ptr *self) {
  index_t index, length = vec_ptr_length(self);
  for (index = length - 1; 0 <= index; index--) {
    void *ptr = vec_ptr_at(self, index);
    vec_ptr_destruct(self, ptr);
  }
  vec_remove(&self->vec, 0, length);
}
