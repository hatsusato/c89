#ifndef INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD
#define INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD

#include "util/type.h"

struct json_pair;
struct json_vec;

struct json {
  const char *key;
  struct json_vec *val;
};

struct json_array {
  struct json_pair *base;
  index_t count;
};

struct json_pair {
  const char *key;
  struct json *val;
};

struct json_vec {
  struct json_array array;
  index_t capacity;
};

#endif /* INCLUDE_GUARD_B6B56A7D_817F_4841_A842_6C0985520EBD */
