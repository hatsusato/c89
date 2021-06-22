#include "unittest.h"

#include <assert.h>

#include "utility/buffer.h"
#include "vec.h"

void vec_unittest(void) {
  struct vec *vec = vec_new(8);
  struct buffer buf;
  int i;
  assert(sizeof(int) < 8);
  assert(vec_length(vec) == 0);
  assert(vec_capacity(vec) == 0);
  vec_reserve(vec, 8);
  assert(vec_length(vec) == 0);
  assert(vec_capacity(vec) == 8);
  for (i = 0; i < 1000; i++) {
    BUFFER_INIT(&buf, &i);
    if (vec_full(vec)) {
      vec_reserve(vec, 0);
    }
    vec_push(vec, &buf);
  }
  assert(vec_length(vec) == 1000);
  assert(vec_capacity(vec) == 1024);
  for (i = 0; i < (int)vec_length(vec); i++) {
    assert(*(int *)vec_at(vec, i) == i);
  }
  for (i = 0; i < 500; i++) {
    vec_pop(vec, NULL);
  }
  assert(vec_length(vec) == 500);
  assert(vec_capacity(vec) == 1024);
  for (i = 0; i < (int)vec_length(vec); i++) {
    assert(*(int *)vec_at(vec, i) == i);
  }
  for (i = 0; i < 1000; i++) {
    BUFFER_INIT(&buf, &i);
    if (vec_full(vec)) {
      vec_reserve(vec, 0);
    }
    vec_push(vec, &buf);
  }
  for (i = 0; i < 500; i++) {
    assert(*(int *)vec_at(vec, i) == i);
  }
  for (i = 0; i < 1000; i++) {
    assert(*(int *)vec_at(vec, 500 + i) == i);
  }
  vec_delete(vec);
}
