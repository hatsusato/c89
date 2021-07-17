#include "str.h"

#include "util/type.h"

struct str {
  index_t len;
  const char *ptr;
};
