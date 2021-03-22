#include "map.h"

#include <stdlib.h>

#include "compare/compare.h"
#include "set/set.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Map {
  Compare *cmp;
  Set *set;
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
static void map_pair_delete(VectorElem pair) {
  UTILITY_FREE(pair);
}
static int map_pair_cmp(CompareElem lhs, CompareElem rhs, CompareExtra extra) {
  const Pair *l = lhs, *r = rhs;
  return compare_cmp(extra, l->key, r->key);
}
static int map_cmp(const void *lhs, const void *rhs) {
  const VectorElem *pl = lhs, *pr = rhs;
  const Pair *l = *pl, *r = *pr;
  return utility_strcmp(l->key, r->key);
}
static void map_sort(const Map *map) {
  VectorElem *base = vector_begin(map->vec);
  Size len = vector_length(map->vec);
  qsort(base, len, sizeof(VectorElem), map_cmp);
}

Map *map_new(void) {
  Map *map = UTILITY_MALLOC(Map);
  map->cmp = compare_new(map_pair_cmp, NULL);
  map->set = set_new(map_pair_delete, map->cmp);
  map->vec = vector_new(map_pair_delete);
  return map;
}
void map_delete(Map *map) {
  vector_delete(map->vec);
  set_delete(map->set);
  compare_delete(map->cmp);
  UTILITY_FREE(map);
}
void map_clear(Map *map) {
  set_clear(map->set);
  vector_clear(map->vec);
}
void map_insert(Map *map, const char *key, MapElem val) {
  set_insert(map->set, map_pair_new(key, val));
  vector_push(map->vec, map_pair_new(key, val));
  map_sort(map);
}
MapElem map_find(Map *map, const char *key) {
  const Pair *found;
  Pair pair = {NULL, NULL};
  pair.key = key;
  found = set_find(map->set, &pair);
  return found ? found->val : NULL;
}
