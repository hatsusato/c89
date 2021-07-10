#include "cell.h"

#include <assert.h>

#include "pool/pool.h"
#include "type.h"
#include "util/box.h"

static const struct cell *cell_new(struct pool *pool, const void *car,
                                   const void *cdr) {
  struct box *box = box_new(sizeof(struct cell), 1);
  struct cell *cell = pool_insert(pool, box);
  cell->car = car;
  cell->cdr = cdr;
  return cell;
}

const struct cell *cell_nil(void) {
  static struct cell cell = {NULL, NULL};
  return &cell;
}
const struct cell *cell_new_cons(struct pool *pool, const struct cell *car,
                                 const struct cell *cdr) {
  assert(car && cdr);
  return cell_new(pool, car, cdr);
}
const struct cell *cell_new_symbol(struct pool *pool, const char *symbol) {
  assert(symbol);
  return cell_new(pool, symbol, NULL);
}
bool_t cell_is_nil(const struct cell *cell) {
  return !cell->car && !cell->cdr;
}
bool_t cell_is_cons(const struct cell *cell) {
  return cell->car && cell->cdr;
}
bool_t cell_is_symbol(const struct cell *cell) {
  return cell->car && !cell->cdr;
}
