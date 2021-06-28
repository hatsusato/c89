#include "str.h"

#include "str/str.h"
#include "util/buffer.h"
#include "vec/vec.h"

static const char *pool_str_push(struct pool_str *self, const struct str *str) {
  struct buffer buf;
  buffer_init(&buf, (void *)str_ptr(str), str_length(str));
  return pool_insert(&self->pool, &buf);
}
static void pool_str_table_insert(struct pool_str *self, const char *ptr,
                                  index_t len) {
  struct str str;
  str_init(&str, ptr, len);
  vec_push(&self->table, &str);
}

void pool_str_new(struct pool_str *self) {
  pool_new(&self->pool);
  vec_new(&self->table, sizeof(struct str));
}
void pool_str_delete(struct pool_str *self) {
  pool_delete(&self->pool);
  vec_delete(&self->table);
}
const char *pool_str_insert(struct pool_str *self, const struct str *str) {
  const char *ptr = pool_str_push(self, str);
  pool_str_table_insert(self, ptr, str_length(str));
  return ptr;
}
