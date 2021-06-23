#include "str.h"

#include <string.h>

void str_init(struct str *self, const char *str) {
  self->ptr = str;
  self->len = str ? strlen(str) : 0;
}
