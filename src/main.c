#include <stdio.h>

#include "cell/print.h"
#include "pool/pool.h"
#include "printer/printer.h"
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
    struct pool *pool = pool_new();
    struct set *symbols = set_new();
    const struct cell *cell = scanner_parse(pool, symbols);
    if (cell) {
      struct printer *printer = printer_new(stdout);
      cell_print(cell, printer);
      printer_delete(printer);
    } else {
      util_error("ERROR: failed to parse");
    }
    set_delete(symbols);
    pool_delete(pool);
  }
  return 0;
}
