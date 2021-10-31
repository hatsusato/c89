#ifndef INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB
#define INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB

#include "util/type.h"

struct json;

struct json_map {
  index_t index;
  const char *key;
  struct json *val;
  void *extra;
};
typedef void (*json_map_t)(struct json_map *);

#endif /* INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB */
