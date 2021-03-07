#include "map.h"

#include "map/pair.h"
#include "pool/pool.h"
#include "utility.h"

struct struct_Map {
  Pool *pool;
};

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  Compare *compare = pair_new_compare(keycmp);
  map->pool = pool_new(pair_delete, compare);
  return map;
}
void map_delete(Map *map) {
  pool_delete(map->pool);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  pool_clear(map->pool);
}
void map_insert(Map *map, ElemType key, ElemType val) {
  pool_insert(map->pool, pair_new(key, val));
}
ElemType *map_find(Map *map, ElemType key) {
  Pair pair = pair_dummy(key);
  const ElemType *found = pool_find(map->pool, &pair);
  return found ? pair_val(*found) : NULL;
}
