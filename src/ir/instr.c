#include "instr.h"

#include "json/json.h"
#include "util/util.h"

struct json *ir_instr_new(const char *tag) {
  struct json *instr = json_new_obj();
  json_insert(instr, tag, json_null());
  return instr;
}
void ir_instr_set_numbering(struct json *instr, int num) {
  struct json *reg = json_new_int(num);
  assert(!ir_instr_has_numbering(instr));
  json_insert(instr, "reg", reg);
  json_del(reg);
}
bool_t ir_instr_has_numbering(struct json *instr) {
  return json_has(instr, "reg");
}
