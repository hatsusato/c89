#include "set.h"

#include "json.h"
#include "util/util.h"

struct json_set {
  struct json_obj *set;
};

struct json_set *json_set_new(void) {
  struct json_set *self = util_malloc(sizeof(struct json_set));
  self->set = json_obj_new();
  return self;
}
void json_set_del(struct json_set *self) {
  json_obj_del(self->set);
  util_free(self);
}
