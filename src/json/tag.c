#include "tag.h"

#include "type.h"
#include "util/util.h"

enum json_tag json_tag(struct json *self) {
  return self->tag;
}
void *json_data(struct json *self) {
  return self->data;
}
