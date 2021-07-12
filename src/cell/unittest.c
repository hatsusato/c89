#include "unittest.h"

#include <assert.h>
#include <string.h>

#include "cell.h"
#include "pool/pool.h"

void cell_unittest(void) {
  const char *a = "aaaaa";
  struct pool *pool = pool_new();
  const struct cell *cell;
  int i;
  cell = cell_nil();
  for (i = 0; i < 5; i++) {
    cell = cell_push(pool, cell, cell_new_symbol(pool, a + i));
  }
  for (i = 0; cell_is_cons(cell); cell = cell_cdr(cell)) {
    const struct cell *car = cell_car(cell);
    const char *symbol;
    assert(cell_is_symbol(car));
    symbol = cell_symbol(car);
    assert(strcmp(a + i, symbol) == 0);
    i++;
  }
  assert(cell_is_nil(cell));
  pool_delete(pool);
}
