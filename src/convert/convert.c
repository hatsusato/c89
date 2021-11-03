#include "convert.h"

#include "util/util.h"

struct convert {
  struct json_factory *factory;
};

void convert(struct json_factory *factory, struct json *json) {
  UTIL_UNUSED(factory);
  UTIL_UNUSED(json);
}
