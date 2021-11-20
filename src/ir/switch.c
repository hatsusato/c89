#include "switch.h"

#include "json/json.h"

struct json *ir_switch_new(void) {
  struct json *self = json_new_obj();
  return self;
}
