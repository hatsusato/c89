#include "pool/pool.h"
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
    scanner_parse(pool);
    pool_delete(pool);
  }
  return 0;
}
