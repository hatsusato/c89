#ifndef INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284
#define INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284

struct json;

typedef void (*json_map_t)(const char *, struct json *, void *);

struct json_map {
  json_map_t map;
  void *extra;
};

#endif /* INCLUDE_GUARD_B3786200_8182_4167_B88A_47D1C9AAB284 */
