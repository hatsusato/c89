#include "str.h"

#include "pool.h"
#include "vec/vec.h"

enum { pool_str_initial_capacity = 8, pool_str_block_size = 4096 };

static void pool_str_new_pool(struct vec *self) {
  struct pool pool;
  pool_malloc(&pool, pool_str_block_size);
  vec_init(self, sizeof(struct pool));
  vec_malloc(self, pool_str_initial_capacity);
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
  enum { initial_capacity = 8 };
  pool_str_new_pool(&self->pool);
  vec_init(&self->table, sizeof(const char *));
  vec_malloc(&self->table, initial_capacity);
  vec_init(&self->big, sizeof(const char *));
  vec_malloc(&self->big, initial_capacity);
}
void pool_str_delete(struct pool_str *self) {
  pool_str_delete_pool(&self->pool);
  vec_free(&self->table);
  vec_free(&self->big);
}
