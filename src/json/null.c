#include "null.h"

#include "tag.h"
#include "type.h"
#include "util/type.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL, NULL};
  return &null;
}
