#include "map.h"

void json_map_apply(struct json_map *self, const char *key, struct json *val) {
  self->map(key, val, self->extra);
}
