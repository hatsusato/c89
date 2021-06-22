#include "vec_ptr.h"

#include "utility/buffer.h"
#include "vec.h"

static struct vec_ptr *vec_ptr_malloc(void) {
  struct buffer buf;
  BUFFER_MALLOC(&buf, struct vec_ptr);
  return (struct vec_ptr *)buf.ptr;
}

struct vec_ptr *vec_ptr_new(void) {
  enum { initial_count = 8 };
  struct vec_ptr *self = vec_ptr_malloc();
  vec_init(&self->vec, sizeof(void *));
  vec_alloc(&self->vec, initial_count);
  return self;
}
