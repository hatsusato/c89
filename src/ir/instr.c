#include "instr.h"

#include "json/json.h"

struct json *ir_instr_new(const char *tag) {
  struct json *instr = json_new_obj();
  struct json *str = json_new_str(tag);
  json_insert(instr, "instr", str);
  json_del(str);
  return instr;
}
