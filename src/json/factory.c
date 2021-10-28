#include "factory.h"

#include "pool/pool.h"
#include "type.h"
#include "util/util.h"

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
