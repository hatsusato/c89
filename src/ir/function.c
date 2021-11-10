#include "function.h"

#include "instr.h"
#include "json/json.h"

static struct json *ir_block_new(void) {
  struct json *block = json_new_obj();
  struct json *array = json_new_arr();
  json_insert(block, "block", array);
  json_del(array);
  return block;
}

void ir_function_init(struct json *function, struct json *name) {
  struct json *array = json_new_arr();
  struct json *alloc = json_new_arr();
  json_insert(function, "function", array);
  json_del(array);
  json_insert(function, "alloc", alloc);
  json_del(alloc);
  json_insert(function, "name", name);
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
void ir_function_push_block(struct json *function) {
  struct json *array = json_get(function, "function");
  struct json *block = ir_block_new();
  json_push(array, block);
  json_insert(function, "current", block);
  json_del(block);
}
struct json *ir_function_new_instr(struct json *function, const char *tag) {
  struct json *instr = ir_instr_new(tag);
  struct json *block = json_get(function, "current");
  struct json *array = json_get(block, "block");
  json_push(array, instr);
  return instr;
}
struct json *ir_function_new_alloca(struct json *function) {
  struct json *alloc = json_get(function, "alloc");
  struct json *instr = ir_instr_new("alloca");
  json_push(alloc, instr);
  return instr;
}
