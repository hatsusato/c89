#include "default.h"

#include "json/json.h"
#include "json/visitor.h"
#include "util/symbol.h"

bool_t convert_default_labeled_statement(struct json *json) {
  return json_has(json, SYMBOL_DEFAULT);
}
static void convert_default_visitor(struct json_visitor *visitor,
                                    struct json *json) {
  json_visit_foreach(visitor, json);
}

void convert_default(struct json *json) {
  json_visit(convert_default_visitor, NULL, json);
}
