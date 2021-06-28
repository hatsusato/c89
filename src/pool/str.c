#include "str.h"

#include "pool.h"
#include "vec/vec.h"

static void pool_str_new_pool_malloc(struct vec *self) {
  enum { pool_str_block_size = 4096 };
  struct pool pool;
  pool_malloc(&pool, pool_str_block_size);
  vec_push(self, &pool);
}
static void pool_str_delete_pool(struct vec *self) {
  index_t index, len = vec_length(self);
  for (index = 0; index < len; index++) {
    pool_free(vec_at(self, index));
  }
  vec_free(self);
}

void pool_str_new(struct pool_str *self) {
  vec_new(&self->pool, sizeof(struct pool));
  pool_str_new_pool_malloc(&self->pool);
  vec_new(&self->table, sizeof(const char *));
  vec_new(&self->big, sizeof(const char *));
}
void pool_str_delete(struct pool_str *self) {
  pool_str_delete_pool(&self->pool);
  vec_free(&self->table);
  vec_free(&self->big);
}
