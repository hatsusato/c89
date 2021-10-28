#include "factory.h"

#include "pool/pool.h"
#include "type.h"
#include "util/util.h"
#include "vec.h"

struct json *json_factory_alloc(struct json_factory *self, enum json_tag tag) {
  struct json *json = pool_alloc(self->pool, sizeof(struct json));
  json->tag = tag;
  json->str = NULL;
  json->vec = NULL;
  return json;
}

struct json_factory *json_factory_new(struct pool *pool) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->pool = pool;
  return self;
}
void json_factory_delete(struct json_factory *self) {
  util_free(self);
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
