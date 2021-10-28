#ifndef INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD
#define INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD

#include "util/type.h"

struct json_pair;
struct json_vec;

struct json {
  const char *str;
  struct json_vec *vec;
};

struct json_vec {
  struct json_pair *base;
  index_t count, capacity;
};

#endif /* INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD */
