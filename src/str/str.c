#include "str.h"

#include "util/buffer.h"
#include "util/util.h"
#include "view.h"

struct str {
  index_t len;
  const char *ptr;
};

static void str_init(struct str *self, const char *ptr) {
  static const char zero = '\0';
  struct buffer src, dst;
  index_t len = self->len;
  buffer_init(&dst, (void *)self->ptr, len + 1);
  buffer_init(&src, (void *)ptr, len);
  buffer_copy(&dst, 0, &src);
  buffer_init(&src, (void *)&zero, 1);
  buffer_copy(&dst, len, &src);
}

struct str *str_new(const struct str_view *view) {
  struct str *self = util_malloc(sizeof(struct str), 1);
  self->len = str_view_length(view);
  self->ptr = util_malloc(1, self->len + 1);
  str_init(self, str_view_ptr(view));
  return self;
}
void str_delete(struct str *self) {
  util_free(self->ptr);
  util_free(self);
}
const char *str_ptr(const struct str *self) {
  return self->ptr;
}
index_t str_len(const struct str *self) {
  return self->len;
}
