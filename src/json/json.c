#include "json.h"

#include "type.h"

struct json *json_null(void) {
  static struct json null = {JSON_TAG_NULL, NULL, NULL};
  return &null;
}
