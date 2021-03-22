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
static void map_pair_delete(VectorElem pair) {
  UTILITY_FREE(pair);
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
static const Pair *map_search(const Map *map, const char *key) {
  VectorElem *base = vector_begin(map->vec);
  Size len = vector_length(map->vec);
  const VectorElem *found = NULL;
  Pair pair = {NULL, NULL};
  const Pair *p = &pair;
  pair.key = key;
  found = bsearch(&p, base, len, sizeof(VectorElem), map_cmp);
  return found ? *found : NULL;
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
  map_sort(map);
}
MapElem map_find(Map *map, const char *key) {
  const Pair *found = map_search(map, key);
  return found ? found->val : NULL;
}
