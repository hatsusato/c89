#ifndef INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F
#define INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F

#include "array/array.h"
#include "util/buffer.h"

struct vec {
  struct array array;
  index_t capacity;
};

struct vec_ptr {
  struct vec vec;
  void (*dtor)(void *);
};

#endif /* INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F */
