#ifndef INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F
#define INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F

#include "array/array.h"

struct box;

struct vec {
  struct array array;
  struct box *box;
};

struct vec_ptr {
  struct vec vec;
};

#endif /* INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F */
