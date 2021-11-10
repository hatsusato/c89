#include "instr.h"

#include "json/json.h"

struct json *ir_instr_new(const char *tag) {
  struct json *instr = json_new_obj();
  json_insert(instr, tag, json_null());
  return instr;
}
