#include "json/factory.h"
#include "json/json.h"
#include "scanner/parse.h"
#include "unittest.h"
#include "util/util.h"

bool_t is_unittest(int argc, char *argv[]) {
  index_t i;
  for (i = 1; i < argc; i++) {
    if (util_streq(argv[i], "--unittest")) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (is_unittest(argc, argv)) {
    unittest();
  } else {
    struct json_factory *factory = json_factory_new();
    struct json *json = scanner_parse(factory);
    if (json_is_null(json)) {
      util_error("ERROR: failed to parse");
    } else {
      json_print(json);
    }
    json_factory_delete(factory);
  }
  return 0;
}
