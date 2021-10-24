#ifndef INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F
#define INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F

#include "array/type.h"
#include "util/box_type.h"

struct box;

struct vec_array {
  byte_t *ptr;
  align_t align;
  index_t count;
};

struct vec {
  struct array array;
  struct box box;
};

struct vec_ptr {
  struct vec_array array;
  index_t capacity;
};

#endif /* INCLUDE_GUARD_05A3735D_C33C_4CD4_AF36_3968DD09F48F */
