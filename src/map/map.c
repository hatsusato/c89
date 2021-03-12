#include "map.h"

#include "map/pair.h"
#include "set/set.h"
#include "utility/utility.h"

struct struct_Map {
  Set *set;
};

static void map_delete_pair(VectorElem pair) {
  pair_delete(pair);
}

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  Compare *compare = pair_new_compare(keycmp);
  map->set = set_new(map_delete_pair, compare);
  return map;
}
void map_delete(Map *map) {
  set_delete(map->set);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  set_clear(map->set);
}
void map_insert(Map *map, CompareElem key, CompareElem val) {
  set_insert(map->set, pair_new(key, val));
}
CompareElem *map_find(Map *map, CompareElem key) {
  Pair pair = pair_dummy(key);
  const CompareElem *found = set_find(map->set, &pair);
  return found ? pair_val((Pair *)*found) : NULL;
}
