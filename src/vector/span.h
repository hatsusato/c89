#ifndef INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA
#define INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA

#include "utility/type.h"

struct vector_span {
  byte_t *begin, *end;
  size_t size;
};

void vector_span_init(struct vector_span *, byte_t *, size_t);

#endif /* INCLUDE_GUARD_55419819_A196_4816_9A82_349ADA502BAA */
