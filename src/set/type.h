#ifndef INCLUDE_GUARD_5C0909A8_A60A_4157_B759_E43DD4529228
#define INCLUDE_GUARD_5C0909A8_A60A_4157_B759_E43DD4529228

#include "vec/type.h"

struct box;
struct vec_ptr;

struct set {
  struct vec vec;
  align_t align;
  cmp_t cmp;
};

struct set_symbol {
  struct vec_ptr *vec;
};

#endif /* INCLUDE_GUARD_5C0909A8_A60A_4157_B759_E43DD4529228 */
