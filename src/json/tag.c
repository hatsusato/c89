#include "tag.h"

#include "type.h"
#include "util/util.h"

enum json_tag json_tag(struct json *self) {
  return self->tag;
}
void *json_data(struct json *self) {
  return self->data;
}
void json_increment(struct json *self) {
  if (self->tag != JSON_TAG_NULL) {
    self->references++;
  }
  assert(0 <= self->references);
}
void json_decrement(struct json *self) {
  if (self->tag != JSON_TAG_NULL) {
    self->references--;
  }
  assert(0 <= self->references);
}
