#include "str.h"

#include <string.h>

#include "pool.h"
#include "str/view.h"
#include "str/view_type.h"
#include "str_type.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

static int pool_str_cmp(const void *lhs, const void *rhs) {
  return str_view_cmp(lhs, rhs);
}
static const struct str_view *pool_str_search(const struct pool_str *self,
                                              const struct str_view *str) {
  return vec_search(&self->table, str, pool_str_cmp);
}
static const char *pool_str_insert_pool(struct pool_str *self,
                                        const struct str_view *str) {
  static char zero = '\0';
  index_t len = str_view_length(str);
  struct box *box;
  struct buffer buf;
  box = box_new(1, len + 1);
  box_buffer(box, &buf);
  buffer_copy2(&buf, 0, str_view_ptr(str), len);
  buffer_copy2(&buf, len, &zero, 1);
  return pool_insert(self->pool, box);
}

void pool_str_init(struct pool_str *self, struct pool *pool) {
  self->pool = pool;
  vec_init(&self->table, sizeof(struct str_view));
}
void pool_str_finish(struct pool_str *self) {
  vec_finish(&self->table);
}
const char *pool_str_insert(struct pool_str *self, const char *str) {
  struct str_view buf;
  str_view_init(&buf, str, strlen(str));
  if (!pool_str_search(self, &buf)) {
    vec_push(&self->table, &buf);
    vec_sort(&self->table, pool_str_cmp);
  }
  return str_view_ptr(pool_str_search(self, &buf));
}
const char *pool_str_canonicalize(struct pool_str *self,
                                  const struct str_view *str) {
  if (!pool_str_search(self, str)) {
    struct str_view buf;
    const char *ptr = pool_str_insert_pool(self, str);
    str_view_init(&buf, ptr, str_view_length(str));
    vec_push(&self->table, &buf);
    vec_sort(&self->table, pool_str_cmp);
  }
  return str_view_ptr(pool_str_search(self, str));
}
