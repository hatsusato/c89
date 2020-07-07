#include "utility.h"

#include <string.h>

Bool utility_str_eq(const char* lhs, const char* rhs) {
  return lhs && rhs && 0 == strcmp(lhs, rhs);
}
