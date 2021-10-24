#ifndef INCLUDE_GUARD_9D60F8E6_3A46_4FB3_8780_52EC0760E6FD
#define INCLUDE_GUARD_9D60F8E6_3A46_4FB3_8780_52EC0760E6FD

#include "util/type.h"

struct slice {
  align_t align;
  const byte_t *ptr;
  index_t len;
};

#endif /* INCLUDE_GUARD_9D60F8E6_3A46_4FB3_8780_52EC0760E6FD */
