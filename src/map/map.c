#include "map.h"

#include "compare/compare.h"
#include "map/pair.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Map {
  Compare *cmp;
  Set *set;
};

static void map_delete_pair(VectorElem pair) {
  pair_delete(pair);
}

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  map->cmp = pair_new_compare(keycmp);
  map->set = set_new(map_delete_pair, map->cmp);
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
void map_insert(Map *map, CompareElem key, CompareElem val) {
  set_insert(map->set, pair_new(key, val));
}
CompareElem map_find(Map *map, CompareElem key) {
  const CompareElem *found;
  Pair pair = {NULL, NULL};
  pair.key = key;
  found = set_find(map->set, &pair);
  return found ? ((Pair *)*found)->val : NULL;
}
