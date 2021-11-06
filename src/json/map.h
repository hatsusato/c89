#ifndef INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284
#define INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284

#include "util/type.h"

struct json;
struct json_map;

typedef void (*json_map_t)(struct json_map *);

struct json_map {
  json_map_t map;
  void *extra;
  index_t index;
  const char *key;
  struct json *val;
};

void *json_map_extra(struct json_map *);
index_t json_map_index(struct json_map *);
const char *json_map_key(struct json_map *);
struct json *json_map_val(struct json_map *);

#endif /* INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284 */
