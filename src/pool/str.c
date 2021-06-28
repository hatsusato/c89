#include "str.h"

#include "str/str.h"
#include "util/buffer.h"
#include "vec/vec.h"

void pool_str_new(struct pool_str *self) {
  pool_new(&self->pool);
  vec_new(&self->table, sizeof(const char *));
}
void pool_str_delete(struct pool_str *self) {
  pool_delete(&self->pool);
  vec_delete(&self->table);
}
const char *pool_str_insert(struct pool_str *self, const struct str *str) {
  struct buffer buf;
  buffer_init(&buf, (void *)str_ptr(str), str_length(str));
  return pool_insert(&self->pool, &buf);
}
