#include "map.h"

#include "compare.h"
#include "set.h"
#include "types.h"
#include "utility.h"

struct struct_Map {
  Set *set;
};
typedef struct {
  ElemType key, val;
} Pair;

static int map_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Pair *l = lhs, *r = rhs;
  return compare_cmp(extra, l->key, r->key);
}

Map *map_new(Compare *keycmp) {
  Map *map = UTILITY_MALLOC(Map);
  Compare *compare = compare_new(map_compare);
  compare_set_extra(compare, keycmp, (Destructor)compare_delete);
  map->set = set_new(NULL, compare);
  return map;
}
void map_delete(Map *map) {
  set_delete(map->set);
  UTILITY_FREE(map);
}
