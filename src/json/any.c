#include "any.h"

#include "util/util.h"

struct json_any {
  void *any;
};

struct json_any *json_any_new(void *any) {
  struct json_any *self = util_malloc(sizeof(struct json_any));
  self->any = any;
  return self;
}
void json_any_delete(struct json_any *self) {
  util_free(self);
}
void *json_any_get(struct json_any *self) {
  return self->any;
}
void json_any_set(struct json_any *self, void *any) {
  self->any = any;
}
