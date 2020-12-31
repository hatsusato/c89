#include "map.h"

#include "compare.h"
#include "map/pair.h"
#include "pool.h"
#include "set.h"
#include "utility.h"

struct struct_Map {
  Pool *pool;
  Set *set;
};

static int pair_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  return compare_cmp(extra, pair_key(lhs), pair_key(rhs));
}

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  Compare *compare = pair_new_compare(keycmp);
  Compare *tmp_compare = compare_new(pair_compare);
  compare_set_extra(tmp_compare, keycmp, NULL);
  map->pool = pool_new(pair_delete, compare);
  map->set = set_new(pair_delete, tmp_compare);
  return map;
}
void map_delete(Map *map) {
  set_delete(map->set);
  pool_delete(map->pool);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  set_clear(map->set);
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
