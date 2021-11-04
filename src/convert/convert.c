#include "convert.h"

#include "json/json.h"
#include "scanner/symbol.h"
#include "util/util.h"

struct convert {
  struct json_factory *factory;
};

struct json *convert_get_identifier(struct json *json) {
  while (!json_is_null(json)) {
    json = json_get(json, SYMBOL_DIRECT_DECLARATOR);
    if (json_has(json, SYMBOL_IDENTIFIER)) {
      return json_get(json, SYMBOL_IDENTIFIER);
    }
  }
  return json;
}
void convert(struct json_factory *factory, struct json *json) {
  UTIL_UNUSED(factory);
  UTIL_UNUSED(json);
}
