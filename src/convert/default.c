#include "default.h"

#include "json/visitor.h"
#include "util/type.h"

static void convert_default_visitor(struct json_visitor *visitor,
                                    struct json *json) {
  json_visit_foreach(visitor, json);
}

void convert_default(struct json *json) {
  json_visit(convert_default_visitor, NULL, json);
}
