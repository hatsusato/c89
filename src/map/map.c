#include "map.h"

#include "compare/compare.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Map {
  Compare *cmp;
  Set *set;
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
static void map_pair_delete(VectorElem pair) {
  UTILITY_FREE(pair);
}
static int map_pair_cmp(CompareElem lhs, CompareElem rhs, CompareExtra extra) {
  const Pair *l = lhs, *r = rhs;
  return compare_cmp(extra, l->key, r->key);
}

Map *map_new(void) {
  Map *map = UTILITY_MALLOC(Map);
  map->cmp = compare_new(map_pair_cmp, NULL);
  map->set = set_new(map_pair_delete, map->cmp);
  return map;
}
void map_delete(Map *map) {
  set_delete(map->set);
  compare_delete(map->cmp);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  set_clear(map->set);
}
void map_insert(Map *map, const char *key, MapElem val) {
  set_insert(map->set, map_pair_new(key, val));
}
MapElem map_find(Map *map, const char *key) {
  const Pair *found;
  Pair pair = {NULL, NULL};
  pair.key = key;
  found = set_find(map->set, &pair);
  return found ? found->val : NULL;
}
