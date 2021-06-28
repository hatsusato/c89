#include "str.h"

#include <stdlib.h>
#include <string.h>

#include "pool.h"
#include "str/str.h"
#include "vec/vec.h"

enum { pool_str_block_size = 4096 };
static void pool_str_pool_malloc(struct vec *self) {
  struct pool pool;
  pool_malloc(&pool, pool_str_block_size);
  vec_push(self, &pool);
}
static void pool_str_pool_free(void *self) {
  pool_free(self);
}
static const char *pool_str_big_malloc(const struct str *str) {
  index_t len = str_length(str);
  char *ptr = malloc(len + 1);
  strncpy(ptr, str_ptr(str), str_length(str));
  ptr[len] = 0;
  return ptr;
}
static void pool_str_big_free(void *self) {
  free(*(void **)self);
}
static const char *pool_str_push(struct vec *self, const struct str *str) {
  struct pool *pool = vec_at(self, vec_length(self) - 1);
  struct buffer buf;
  buffer_init(&buf, (void *)str_ptr(str), str_length(str));
  return pool_insert(pool, &buf);
}

void pool_str_new(struct pool_str *self) {
  vec_new(&self->pool, sizeof(struct pool));
  pool_str_pool_malloc(&self->pool);
  vec_new(&self->table, sizeof(const char *));
  vec_new(&self->big, sizeof(const char *));
}
void pool_str_delete(struct pool_str *self) {
  vec_delete(&self->pool, pool_str_pool_free);
  vec_delete(&self->table, NULL);
  vec_delete(&self->big, pool_str_big_free);
}
const char *pool_str_insert(struct pool_str *self, const struct str *str) {
  const char *ptr;
  if (str_length(str) < pool_str_block_size / 4) {
    ptr = pool_str_push(&self->pool, str);
    if (!ptr) {
      pool_str_pool_malloc(&self->pool);
      ptr = pool_str_push(&self->pool, str);
    }
  } else {
    ptr = pool_str_big_malloc(str);
    vec_push(&self->big, &ptr);
  }
  return ptr;
}
