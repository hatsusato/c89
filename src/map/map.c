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

static int pair_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  const Pair *l = lhs, *r = rhs;
  return compare_cmp(extra, l->key, r->key);
}
static Pair *pair_new(ElemType key, ElemType val) {
  Pair *pair = UTILITY_MALLOC(Pair);
  pair->key = key;
  pair->val = val;
  return pair;
}
static void pair_delete(ElemType pair) {
  UTILITY_FREE(pair);
}

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
