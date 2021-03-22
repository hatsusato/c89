#include "map.h"

#include <stdlib.h>

#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Map {
  Vector *vec;
};
typedef struct {
  const char *key;
  MapElem val;
} Pair;

static Pair *map_pair_new(const char *key, MapElem val) {
  Pair *pair = UTILITY_MALLOC(Pair);
  pair->key = key;
  pair->val = val;
  return pair;
}
static void map_pair_delete(Generic pair) {
  UTILITY_FREE(pair);
}
static int map_cmp(const ConstGeneric *lhs, const ConstGeneric *rhs) {
  const Pair *l = *lhs, *r = *rhs;
  return utility_strcmp(l->key, r->key);
}

Map *map_new(void) {
  Map *map = UTILITY_MALLOC(Map);
  map->vec = vector_new(map_pair_delete);
  return map;
}
void map_delete(Map *map) {
  vector_delete(map->vec);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  vector_clear(map->vec);
}
void map_insert(Map *map, const char *key, MapElem val) {
  vector_push(map->vec, map_pair_new(key, val));
  vector_sort(map->vec, map_cmp);
}
MapElem map_find(Map *map, const char *key) {
  const Pair *found = NULL;
  Pair pair = {NULL, NULL};
  pair.key = key;
  found = vector_search(map->vec, &pair, map_cmp);
  return found ? found->val : NULL;
}
