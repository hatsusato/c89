#include "immediate.h"

#include "json/json.h"
#include "json/visitor.h"
#include "util/symbol.h"
#include "util/util.h"

static void convert_immediate_primary_expression(struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    struct json *val = json_get(json, SYMBOL_INTEGER_CONSTANT);
    int num = util_atoi(json_get_str(val));
    json_set(json, "immediate", json_new_int(num));
  }
}
static void convert_immediate_expression(struct json *json) {
  const char *tag = json_get_str(json_get(json, "tag"));
  if (util_streq(tag, SYMBOL_PRIMARY_EXPRESSION)) {
    convert_immediate_primary_expression(json);
  }
}
static void convert_immediate_visitor(struct json_visitor *visitor,
                                      struct json *json) {
  if (json_has(json, SYMBOL_EXPRESSION)) {
    convert_immediate_expression(json_get(json, SYMBOL_EXPRESSION));
  } else {
    json_visit_foreach(visitor, json);
  }
}

void convert_immediate(struct json *json) {
  json_visit(convert_immediate_visitor, NULL, json);
}
