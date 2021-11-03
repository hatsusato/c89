#include "type.h"

#include "util/util.h"

struct json *json_alloc(enum json_tag tag, void *data) {
  struct json *self = util_malloc(sizeof(struct json));
  self->tag = tag;
  self->data = data;
  return self;
}
void json_free(struct json *self) {
  util_free(self);
}
