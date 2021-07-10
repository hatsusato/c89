#include "cell.h"

#include "pool/pool.h"
#include "type.h"
#include "util/box.h"

const struct cell *cell_new(struct pool *pool, const void *car,
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
