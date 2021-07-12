#include "pool/pool.h"
#include "scanner/scanner.h"
#include "unittest.h"
#include "util/util.h"

int main(int argc, char *argv[]) {
  struct pool *pool = pool_new();
  const struct cell *ast = scanner_parse(pool);
  UTIL_UNUSED(argc);
  UTIL_UNUSED(argv);
  UTIL_UNUSED(ast);
  unittest();
  pool_delete(pool);
  return 0;
}
