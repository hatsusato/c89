#include "str.h"

#include <assert.h>
#include <string.h>

#include "type.h"
#include "util/util.h"

void str_view_init(struct str_view *self, const char *str, index_t len) {
  assert(0 <= len);
  assert(str || len == 0);
  self->ptr = str;
  self->len = len;
}
void str_view_set(struct str_view *self, const char *str) {
  str_view_init(self, str, str ? strlen(str) : 0);
}
const char *str_view_ptr(const struct str_view *self) {
  return self->ptr;
}
index_t str_view_length(const struct str_view *self) {
  return self->len;
}
void str_view_remove_prefix(struct str_view *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->ptr += count;
    self->len -= count;
  } else {
    str_view_set(self, NULL);
  }
}
void str_view_remove_suffix(struct str_view *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->len -= count;
  } else {
    str_view_set(self, NULL);
  }
}
int str_view_cmp(const struct str_view *lhs, const struct str_view *rhs) {
  int ret = strncmp(lhs->ptr, rhs->ptr, UTIL_MIN(lhs->len, rhs->len));
  return (ret == 0) ? lhs->len - rhs->len : ret;
}
