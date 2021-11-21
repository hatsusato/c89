#include "convert.h"

#include "immediate.h"
#include "return.h"
#include "switch.h"

void convert(struct json *json) {
  convert_immediate(json);
  convert_return(json);
  convert_switch(json);
}
