#include "vec_ptr.h"

#include "utility/buffer.h"
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

struct vec_ptr *vec_ptr_new(void) {
  enum { initial_count = 8 };
  struct vec_ptr *self = vec_ptr_malloc();
  vec_init(&self->vec, sizeof(void *));
  vec_alloc(&self->vec, initial_count);
  return self;
}
void vec_ptr_delete(struct vec_ptr *self) {
  vec_reset(&self->vec);
  vec_ptr_free(self);
}
index_t vec_ptr_capacity(struct vec_ptr *self) {
  return vec_capacity(&self->vec);
}
index_t vec_ptr_length(struct vec_ptr *self) {
  return vec_length(&self->vec);
}
