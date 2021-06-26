#include "vec_ptr.h"

#include "type.h"
#include "util/buffer.h"
#include "util/range.h"
#include "util/slice.h"
#include "vec.h"

static struct vec_ptr *vec_ptr_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec_ptr);
  return buffer_at(&buf, 0);
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
  struct buffer buf;
  struct slice slice;
  BUFFER_INIT(&buf, &ptr);
  slice_init(&slice, sizeof(void *));
  slice_set(&slice, &buf);
  vec_push(&self->vec, &slice);
}
void vec_ptr_pop(struct vec_ptr *self) {
  vec_ptr_destruct(self, vec_ptr_at(self, -1));
  vec_pop(&self->vec);
}
void vec_ptr_clear(struct vec_ptr *self) {
  index_t index, length = vec_ptr_length(self);
  for (index = length - 1; 0 <= index; index--) {
    vec_ptr_destruct(self, vec_ptr_at(self, index));
  }
  vec_clear(&self->vec);
}
