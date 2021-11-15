#include "return.h"

#include "json/visitor.h"
#include "util/type.h"

static void convert_return_visitor(struct json_visitor *visitor,
                                   struct json *json) {
  json_visit_foreach(visitor, json);
}

void convert_return(struct json *json) {
  json_visit(convert_return_visitor, NULL, json);
}
