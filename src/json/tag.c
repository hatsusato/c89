#include "tag.h"

#include "type.h"

enum json_tag json_tag(struct json *json) {
  return json->tag;
}
