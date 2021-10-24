#ifndef INCLUDE_GUARD_E8AA6C9D_1724_4976_81B1_369B234E105F
#define INCLUDE_GUARD_E8AA6C9D_1724_4976_81B1_369B234E105F

#include "type.h"

struct box {
  size_t size;
  const void *ptr;
  const byte_t data[1];
};

#endif /* INCLUDE_GUARD_E8AA6C9D_1724_4976_81B1_369B234E105F */
