#include "expression.h"

#include "json/json.h"
#include "util/symbol.h"

struct json *convert_expression(struct convert_extra *self, struct json *json) {
  if (json_has(json, SYMBOL_INTEGER_CONSTANT)) {
    return json_get(json, SYMBOL_INTEGER_CONSTANT);
  } else {
    return json_null();
  }
  (void)self;
}
