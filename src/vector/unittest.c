#include "unittest.h"

#include <assert.h>

#include "utility/buffer.h"
#include "vec.h"

void vec_unittest(void) {
  struct vec *vec = vec_new(8);
  struct buffer buf;
  index_t i;
  assert(sizeof(int) < 8);
  assert(vec_length(vec) == 0);
  assert(vec_capacity(vec) == 0);
  buffer_malloc(&buf, 8 * 8);
  vec_init(vec, &buf);
  assert(vec_length(vec) == 0);
  assert(vec_capacity(vec) == 8);
  for (i = 0; i < 8; i++) {
    BUFFER_INIT(&buf, &i);
    vec_push(vec, &buf);
  }
  assert(vec_length(vec) == 8);
  assert(vec_capacity(vec) == 8);
  for (i = 0; i < 8; i++) {
    assert(*(int *)vec_at(vec, i) == i);
  }
  assert(vec_length(vec) == 8);
  assert(vec_capacity(vec) == 8);
  vec_delete(vec);
}
