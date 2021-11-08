#include "expression.h"

#include "extra.h"
#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

static struct json *convert_identifier(struct convert_extra *self,
                                       struct json *json) {
  return convert_extra_lookup_symbol(self, json);
}
static struct json *convert_integer_constant(struct convert_extra *self,
                                             struct json *json) {
  UTIL_UNUSED(self);
  return json;
}
static struct json *convert_assignment_expression(struct convert_extra *self,
                                                  struct json *json) {
  struct json *value = convert_expression(self, json_get(json, "rhs"));
  struct json *pointer = convert_lvalue(self, json_get(json, "lhs"));
  struct json *instr = convert_extra_new_instr("store");
  json_insert(instr, "value", value);
  json_insert(instr, "pointer", pointer);
  convert_extra_push_instr(self, instr);
  json_del(instr);
  return instr;
}

struct json *convert_lvalue(struct convert_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_extra_lookup_symbol(self, json_get(json, SYMBOL_IDENTIFIER));
  } else {
    return json;
  }
}
struct json *convert_expression(struct convert_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_IDENTIFIER)) {
    return convert_identifier(self, json_get(json, SYMBOL_IDENTIFIER));
  } else if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    return convert_integer_constant(self,
                                    json_get(json, SYMBOL_INTEGER_CONSTANT));
  } else if (json_has(json, SYMBOL_ASSIGNMENT_EXPRESSION)) {
    return convert_assignment_expression(
        self, json_get(json, SYMBOL_ASSIGNMENT_EXPRESSION));
  } else {
    return json;
  }
}
