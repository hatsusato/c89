#include "switch.h"

#include "json/json.h"
#include "util/symbol.h"

struct json *ir_switch_new(struct json *instr) {
  struct json *self = json_new_obj();
  json_obj_insert(self, SYMBOL_SWITCH_EXTRA_INSTR, instr);
  return self;
}
void ir_switch_insert_default(struct json *self, struct json *block) {
  json_obj_insert(self, SYMBOL_SWITCH_EXTRA_DEFAULT, block);
}
