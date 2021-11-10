#include "function.h"

#include "json/json.h"

struct json *ir_function_new(void) {
  struct json *function = json_new_obj();
  struct json *array = json_new_arr();
  json_insert(function, "function", array);
  json_del(array);
  return function;
}
