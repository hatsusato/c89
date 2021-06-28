#include "str.h"

#include "pool.h"
#include "str/str.h"
#include "vec/vec.h"

static void pool_str_new_pool_malloc(struct vec *self) {
  enum { pool_str_block_size = 4096 };
  struct pool pool;
  pool_malloc(&pool, pool_str_block_size);
  vec_push(self, &pool);
}
static void pool_str_delete_pool_free(void *self) {
  pool_free(self);
}
static const char *pool_str_push(struct vec *self, const struct str *str) {
  struct pool *pool = vec_at(self, vec_length(self) - 1);
  struct buffer buf;
  buffer_init(&buf, (void *)str_ptr(str), str_length(str));
  return pool_insert(pool, &buf);
}

void pool_str_new(struct pool_str *self) {
  vec_new(&self->pool, sizeof(struct pool));
  pool_str_new_pool_malloc(&self->pool);
  vec_new(&self->table, sizeof(const char *));
  vec_new(&self->big, sizeof(const char *));
}
void pool_str_delete(struct pool_str *self) {
  vec_delete(&self->pool, pool_str_delete_pool_free);
  vec_delete(&self->table, NULL);
  vec_delete(&self->big, NULL);
}
const char *pool_str_insert(struct pool_str *self, const struct str *str) {
  const char *ptr = pool_str_push(&self->pool, str);
  if (!ptr) {
    pool_str_new_pool_malloc(&self->pool);
    ptr = pool_str_push(&self->pool, str);
  }
  return ptr;
}
