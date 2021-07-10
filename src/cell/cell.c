#include "cell.h"

#include "type.h"
#include "util/type.h"

const struct cell *cell_nil(void) {
  static struct cell cell = {NULL, NULL};
  return &cell;
}
