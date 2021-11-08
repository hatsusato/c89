#include "expression.h"

#include "extra.h"
#include "json/json.h"
#include "util/symbol.h"

static struct json *convert_assignment_expression(struct convert_extra *self,
                                                  struct json *json) {
  struct json *value = convert_expression(self, json_get(json, "rhs"));
  struct json *pointer = convert_expression(self, json_get(json, "lhs"));
  struct json *instr = convert_extra_new_instr("store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  convert_extra_push_instr(self, instr);
  json_del(instr);
  return instr;
}

struct json *convert_expression(struct convert_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    return json_get(json, SYMBOL_INTEGER_CONSTANT);
  } else if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_assignment_expression(
        self, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
  (void)self;
}
