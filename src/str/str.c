#include "str.h"

#include <string.h>

void str_init(struct str *self, const char *str) {
  self->ptr = str;
  self->len = str ? strlen(str) : 0;
}
void str_remove_prefix(struct str *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->ptr += count;
    self->len -= count;
  } else {
    str_init(self, NULL);
  }
}
void str_remove_suffix(struct str *self, index_t count) {
  if (0 <= count && count < self->len) {
    self->len -= count;
  } else {
    str_init(self, NULL);
  }
}
int str_cmp(const struct str *lhs, const struct str *rhs) {
  index_t len = lhs->len < rhs->len ? lhs->len : rhs->len;
  int ret = strncmp(lhs->ptr, rhs->ptr, len);
  return (ret == 0) ? lhs->len - rhs->len : ret;
}
