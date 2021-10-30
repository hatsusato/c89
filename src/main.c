#include <stdio.h>

#include "json/factory.h"
#include "json/json.h"
#include "json/printer.h"
#include "pool/pool.h"
#include "printer/printer.h"
#include "scanner/parse.h"
#include "set/set.h"
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
    struct pool *pool = pool_new();
    struct set *symbols = set_new();
    struct json *json = scanner_parse(factory, pool, symbols);
    if (json_is_null(json)) {
      util_error("ERROR: failed to parse");
    } else {
      struct printer *printer = printer_new(stdout);
      json_print(json, printer);
      printer_delete(printer);
    }
    set_delete(symbols);
    pool_delete(pool);
    json_factory_delete(factory);
  }
  return 0;
}
