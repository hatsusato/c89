#ifndef INCLUDE_GUARD_5DE865CB_51C5_423B_9398_D7D94EF97355
#define INCLUDE_GUARD_5DE865CB_51C5_423B_9398_D7D94EF97355

#include "util/type.h"

struct slice {
  align_t align;
  const byte_t *ptr;
  index_t len;
};

struct array {
  struct slice slice;
};

#endif /* INCLUDE_GUARD_5DE865CB_51C5_423B_9398_D7D94EF97355 */
