#include "immediate.h"

#include "json/visitor.h"
#include "util/type.h"

static void convert_immediate_visitor(struct json_visitor *visitor,
                                      struct json *json) {
  json_visit_foreach(visitor, json);
}

void convert_immediate(struct json *json) {
  json_visit(convert_immediate_visitor, NULL, json);
}
