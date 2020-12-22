#include "map.h"

#include "compare.h"
#include "map/pair.h"
#include "set.h"
#include "utility.h"

struct struct_Map {
  Set *set;
};

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  Compare *compare = compare_new(pair_compare);
  compare_set_extra(compare, keycmp, (Destructor)compare_delete);
  map->set = set_new(pair_delete, compare);
  return map;
}
void map_delete(Map *map) {
  set_delete(map->set);
  UTILITY_FREE(map);
}
void map_insert(Map *map, ElemType key, ElemType val) {
  set_insert(map->set, pair_new(key, val));
}
ElemType *map_find(Map *map, ElemType key) {
  Pair pair = pair_dummy(key);
  const ElemType *found = set_find(map->set, &pair);
  return found ? pair_val(*found) : NULL;
}
Bool map_contains(const Map *map, ElemType key) {
  Pair pair = pair_dummy(key);
  return set_contains(map->set, &pair);
}
