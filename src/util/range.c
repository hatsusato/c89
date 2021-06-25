#include "range.h"

void range_init(struct range *range, index_t index, index_t count) {
  range->begin = index;
  range->end = index + count;
}
bool_t range_is_valid(const struct range *range) {
  return 0 <= range->begin && range->begin <= range->end;
}
index_t range_count(const struct range *range) {
  return range->end - range->begin;
}
