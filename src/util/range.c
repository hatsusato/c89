#include "range.h"

void range_init(struct range *range, index_t index, index_t count) {
  range->begin = index;
  range->end = index + count;
}
