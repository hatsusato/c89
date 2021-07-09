#include "str.h"

#include "str/str.h"
#include "util/box.h"
#include "util/buffer.h"
#include "vec/vec.h"

static int pool_str_cmp(const void *lhs, const void *rhs) {
  return str_cmp(lhs, rhs);
}
static const struct str *pool_str_search(const struct pool_str *self,
                                         const struct str *str) {
  return vec_search(&self->table, str, pool_str_cmp);
}
static const char *pool_str_insert_pool(struct pool_str *self,
                                        const struct str *str) {
  index_t len = str_length(str);
  struct box *box;
  struct buffer src, dst;
  box = box_new(1, len);
  box_buffer(box, &dst);
  buffer_init(&src, (void *)str_ptr(str), len);
  buffer_memcpy(&dst, 0, &src);
  return pool_insert(&self->pool, box);
}

void pool_str_new(struct pool_str *self) {
  pool_new(&self->pool);
  vec_new(&self->table, sizeof(struct str));
}
void pool_str_delete(struct pool_str *self) {
  pool_delete(&self->pool);
  vec_delete(&self->table);
}
const struct str *pool_str_insert(struct pool_str *self,
                                  const struct str *str) {
  if (!pool_str_search(self, str)) {
    struct str buf;
    const char *ptr = pool_str_insert_pool(self, str);
    str_init(&buf, ptr, str_length(str));
    vec_push(&self->table, &buf);
    vec_sort(&self->table, pool_str_cmp);
  }
  return pool_str_search(self, str);
}
