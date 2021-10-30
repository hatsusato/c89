#include "cell/print.h"
#include "json/factory.h"
#include "pool/pool.h"
#include "scanner/scanner.h"
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
    const struct cell *cell = scanner_parse(factory, pool, symbols);
    if (cell) {
      cell_print(cell);
    } else {
      util_error("ERROR: failed to parse");
    }
    set_delete(symbols);
    pool_delete(pool);
    json_factory_delete(factory);
  }
  return 0;
}
