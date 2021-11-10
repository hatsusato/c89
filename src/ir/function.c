#include "function.h"

#include "json/json.h"

void ir_function_init(struct json *function) {
  struct json *array = json_new_arr();
  struct json *alloc = json_new_arr();
  json_insert(function, "function", array);
  json_del(array);
  json_insert(function, "alloc", alloc);
  json_del(alloc);
}
void ir_function_finish(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *block_array = json_get(function, "function");
  struct json *front = json_front(block_array);
  struct json *block = json_get(front, "block");
  json_append(alloc, block);
  json_insert(front, "block", alloc);
  json_insert(function, "alloc", json_null());
}
