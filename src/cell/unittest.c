#include "unittest.h"

#include <assert.h>

#include "cell.h"
#include "cell/factory.h"
#include "pool/any.h"
#include "pool/pool.h"
#include "set/symbol.h"
#include "util/util.h"

void cell_unittest(void) {
  const char *a = "aaaaa";
  struct pool *pool = pool_new();
  struct pool_any *any = pool_any_new();
  struct set_symbol *symbols = set_symbol_new();
  struct cell_factory *factory = cell_factory_new(any, symbols);
  const struct cell *cell;
  int i;
  cell = cell_nil();
  for (i = 0; i < 5; i++) {
    const struct cell *symbol = cell_factory_symbol(factory, a + i);
    cell = cell_factory_push(factory, cell, symbol);
  }
  for (i = 0; cell_is_cons(cell); cell = cell_cdr(cell)) {
    const struct cell *car = cell_car(cell);
    const char *symbol;
    assert(cell_is_symbol(car));
    symbol = cell_symbol(car);
    assert(util_streq(a + i, symbol));
    i++;
  }
  assert(cell_is_nil(cell));
  cell_factory_delete(factory);
  set_symbol_delete(symbols);
  pool_any_delete(any);
  pool_delete(pool);
}
