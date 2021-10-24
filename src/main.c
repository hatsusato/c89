#include <stdio.h>

#include "cell/print.h"
#include "pool/pool.h"
#include "printer/printer.h"
#include "printer/type.h"
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
    struct pool *any = pool_new();
    struct set *symbols = set_new();
    struct printer printer;
    const struct cell *cell = scanner_parse(any, symbols);
    if (cell) {
      printer_init(&printer, stdout);
      cell_print(cell, &printer);
    } else {
      fprintf(stderr, "ERROR: failed to parse");
    }
    set_delete(symbols);
    pool_delete(any);
  }
  return 0;
}
