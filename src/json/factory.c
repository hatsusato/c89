#include "factory.h"

#include "type.h"
#include "util/util.h"

struct json_factory *json_factory_new(struct pool *pool) {
  struct json_factory *self = util_malloc(sizeof(struct json_factory));
  self->pool = pool;
  return self;
}
void json_factory_delete(struct json_factory *self) {
  util_free(self);
}
