#include "factory.h"

#include "json.h"
#include "map.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

static void json_factory_free(struct json *json, struct json_map_extra *extra) {
  if (json) {
    switch (json->tag) {
    case JSON_TAG_STR:
      json_str_delete(json_as_str(json));
      break;
    case JSON_TAG_ARR:
      json_arr_delete(json_as_arr(json));
      json_vec_delete(json->vec);
      break;
    case JSON_TAG_OBJ:
      json_obj_delete(json_as_obj(json));
      json_vec_delete(json->vec);
      break;
    default:
      break;
    }
  }
  util_free(json);
  UTIL_UNUSED(extra);
}
static struct json *json_factory_alloc(struct json_factory *self,
                                       enum json_tag tag) {
  struct json *json = util_malloc(sizeof(struct json));
  json->tag = tag;
  json->str = NULL;
  json->arr = NULL;
  json->vec = NULL;
  json_vec_push(self->pool, NULL, json);
  return json;
}

struct json_factory *json_factory_new(void) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->pool = json_vec_new();
  return self;
}
void json_factory_delete(struct json_factory *self) {
  struct json_map map = {json_factory_free, NULL};
  json_vec_foreach(self->pool, &map);
  json_vec_delete(self->pool);
  util_free(self);
}
struct json *json_factory_str(struct json_factory *self, const char *str) {
  struct json *json = json_factory_alloc(self, JSON_TAG_STR);
  assert(str);
  json->str = json_str_new(str);
  return json;
}
struct json *json_factory_arr(struct json_factory *self) {
  struct json *json = json_factory_alloc(self, JSON_TAG_ARR);
  json->arr = json_arr_new();
  json->vec = json_vec_new();
  return json;
}
struct json *json_factory_obj(struct json_factory *self) {
  struct json *json = json_factory_alloc(self, JSON_TAG_OBJ);
  json->obj = json_obj_new();
  json->vec = json_vec_new();
  return json;
}
