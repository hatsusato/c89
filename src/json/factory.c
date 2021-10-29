#include "factory.h"

#include "type.h"
#include "util/util.h"
#include "vec.h"

static void json_factory_free(struct json_pair *json) {
  util_free(json->val);
}
static struct json *json_factory_alloc(struct json_factory *self,
                                       enum json_tag tag) {
  struct json *json = util_malloc(sizeof(struct json));
  json->tag = tag;
  json->str = NULL;
  json->vec = NULL;
  json_vec_push(self->vec, NULL, json);
  return json;
}

struct json_factory *json_factory_new(void) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->vec = json_vec_new();
  return self;
}
void json_factory_delete(struct json_factory *self) {
  json_vec_map(self->vec, json_factory_free);
  json_vec_delete(self->vec);
  util_free(self);
}
struct json *json_factory_str(struct json_factory *self, const char *str) {
  struct json *json = json_factory_alloc(self, JSON_TAG_STR);
  assert(str);
  json->str = str;
  return json;
}
struct json *json_factory_arr(struct json_factory *self) {
  struct json *json = json_factory_alloc(self, JSON_TAG_ARR);
  json->vec = json_vec_new();
  return json;
}
struct json *json_factory_obj(struct json_factory *self) {
  struct json *json = json_factory_alloc(self, JSON_TAG_OBJ);
  json->vec = json_vec_new();
  return json;
}
