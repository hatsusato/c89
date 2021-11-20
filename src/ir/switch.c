#include "switch.h"

#include "json/json.h"
#include "util/symbol.h"

struct json *ir_switch_new(struct json *instr) {
  struct json *self = json_new_obj();
  json_obj_insert(self, SYMBOL_SWITCH_EXTRA_INSTR, instr);
  json_obj_set(self, SYMBOL_SWITCH_EXTRA_CASE, json_new_arr());
  return self;
}
void ir_switch_del(struct json *self) {
  struct json *instr = json_obj_get(self, SYMBOL_SWITCH_EXTRA_INSTR);
  json_obj_insert(instr, SYMBOL_INSTR_SWITCH_CASE,
                  json_obj_get(self, SYMBOL_SWITCH_EXTRA_CASE));
  json_obj_insert(instr, SYMBOL_INSTR_SWITCH_DEFAULT,
                  json_obj_get(self, SYMBOL_SWITCH_EXTRA_DEFAULT));
  json_del(self);
}
void ir_switch_insert_default(struct json *self, struct json *block) {
  json_obj_insert(self, SYMBOL_SWITCH_EXTRA_DEFAULT, block);
}
void ir_switch_insert_case(struct json *self, struct json *value,
                           struct json *block) {
  struct json *array = json_obj_get(self, SYMBOL_SWITCH_EXTRA_CASE);
  struct json *elem = json_new_obj();
  json_obj_insert(elem, SYMBOL_SWITCH_EXTRA_VALUE, value);
  json_obj_insert(elem, SYMBOL_SWITCH_EXTRA_DEST, block);
  json_arr_push(array, elem);
  json_del(elem);
}
