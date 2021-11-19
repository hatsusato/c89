#include "convert.h"

#include "default.h"
#include "immediate.h"
#include "return.h"

void convert(struct json *json) {
  convert_immediate(json);
  convert_return(json);
  convert_default(json);
}
