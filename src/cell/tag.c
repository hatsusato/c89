#include "tag.h"

#include "type.h"

const struct cell *cell_tag_symbol(void) {
  static struct cell tag;
  return &tag;
}
