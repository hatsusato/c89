#ifndef INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70
#define INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70

#include "util/buffer.h"

struct array {
  align_t align;
  struct buffer buf;
  index_t len;
};

#endif /* INCLUDE_GUARD_9AEC46FD_3C00_49FC_AB18_C05CB1E03D70 */
