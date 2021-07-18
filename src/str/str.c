#include "str.h"

#include "util/box.h"
#include "util/box_type.h"
#include "util/buffer.h"
#include "util/util.h"
#include "view.h"

struct str {
  struct box box;
  const char *ptr;
};

static void str_init(struct str *self, const char *ptr) {
  static const char zero = '\0';
  struct buffer buf;
  index_t len = str_len(self);
  buffer_init(&buf, self->ptr, len + 1);
  buffer_copy(&buf, 0, ptr, len);
  buffer_copy(&buf, len, &zero, 1);
  box_buffer(&self->box, &buf);
  buffer_copy(&buf, 0, ptr, len);
  buffer_copy(&buf, len, &zero, 1);
}

struct str *str_new(const struct str_view *view) {
  struct str *self = util_malloc(sizeof(struct str), 1);
  index_t len = str_view_length(view);
  self->ptr = util_malloc(1, len + 1);
  box_init(&self->box, 1, len + 1);
  str_init(self, str_view_ptr(view));
  return self;
}
void str_delete(struct str *self) {
  box_finish(&self->box);
  util_free(self->ptr);
  util_free(self);
}
const char *str_ptr(const struct str *self) {
  return self->ptr;
}
index_t str_len(const struct str *self) {
  return box_size(&self->box) - 1;
}
