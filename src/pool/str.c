#include "str.h"

#include "pool.h"
#include "vec/vec.h"

void pool_str_new(struct pool_str *self) {
  enum { initial_capacity = 8, pool_size = 4096 };
  struct pool pool;
  vec_init(&self->pool, sizeof(struct pool));
  vec_malloc(&self->pool, initial_capacity);
  pool_malloc(&pool, pool_size);
  vec_push(&self->pool, &pool);
  vec_init(&self->table, sizeof(const char *));
  vec_malloc(&self->table, initial_capacity);
  vec_init(&self->big, sizeof(const char *));
  vec_malloc(&self->big, initial_capacity);
}
void pool_str_delete(struct pool_str *self) {
  index_t index;
  struct pool *it = vec_at(&self->pool, 0);
  for (index = 0; index < vec_length(&self->pool); index++, it++) {
    pool_free(it);
  }
  vec_free(&self->pool);
  vec_free(&self->table);
  vec_free(&self->big);
}
