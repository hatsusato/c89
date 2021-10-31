#ifndef INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB
#define INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB

#include "util/type.h"

struct json;
struct json_map_extra;
typedef void (*json_map_t)(struct json *, struct json_map_extra *);

struct json_map_extra {
  index_t index;
  const char *key;
  void *extra;
};
struct json_map {
  json_map_t map;
  void *extra;
};

#endif /* INCLUDE_GUARD_06F09559_7A30_4892_876A_9CD8A0B7E7EB */
