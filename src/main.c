#include <stdio.h>

#include "cell/cell.h"
#include "pool/pool.h"
#include "printer/printer.h"
#include "printer/type.h"
#include "scanner/scanner.h"
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
    struct printer printer;
    const struct cell *cell = scanner_parse(pool);
    if (cell) {
      printer_init(&printer, stdout);
      cell_print(cell, &printer);
    } else {
      fprintf(stderr, "ERROR: failed to parse");
    }
    pool_delete(pool);
  }
  return 0;
}
