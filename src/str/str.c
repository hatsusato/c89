#include "str.h"

#include <assert.h>
#include <string.h>

#include "type.h"
#include "util/util.h"

void str_init(struct str *self, const char *str, index_t len) {
  assert(0 <= len);
  assert(str || len == 0);
  self->ptr = str;
  self->len = len;
}
void str_set(struct str *self, const char *str) {
  str_init(self, str, str ? strlen(str) : 0);
}
const char *str_ptr(const struct str *self) {
  return self->ptr;
}
index_t str_length(const struct str *self) {
  return self->len;
}
void str_remove_prefix(struct str *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->ptr += count;
    self->len -= count;
  } else {
    str_set(self, NULL);
  }
}
void str_remove_suffix(struct str *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->len -= count;
  } else {
    str_set(self, NULL);
  }
}
int str_cmp(const struct str *lhs, const struct str *rhs) {
  int ret = strncmp(lhs->ptr, rhs->ptr, UTIL_MIN(lhs->len, rhs->len));
  return (ret == 0) ? lhs->len - rhs->len : ret;
}
