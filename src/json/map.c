#include "map.h"

void *json_map_extra(struct json_map *self) {
  return self->extra;
}
bool_t json_map_is_obj(struct json_map *self) {
  return self->is_obj;
}
index_t json_map_index(struct json_map *self) {
  return self->index;
}
const char *json_map_key(struct json_map *self) {
  return self->key;
}
struct json *json_map_val(struct json_map *self) {
  return self->val;
}
