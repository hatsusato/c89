#include "map.h"

#include "set.h"
#include "utility.h"

struct struct_Map {
  Set *set;
};

Map *map_new(void) {
  Map *map = UTILITY_MALLOC(Map);
  return map;
}
void map_delete(Map *map) {
  UTILITY_FREE(map);
}
