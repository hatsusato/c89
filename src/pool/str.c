#include "str.h"

#include "str/str.h"
#include "util/buffer.h"
#include "vec/vec.h"

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
  struct buffer buf;
  const char *ptr = str_ptr(str);
  index_t len = str_length(str);
  buffer_init(&buf, (void *)ptr, len);
  ptr = pool_insert(&self->pool, &buf);
  pool_str_table_insert(self, ptr, len);
  return ptr;
}
