#include "type.h"

#include "function.h"
#include "json/json.h"
#include "table.h"

static struct json *convert_get_alloc(struct convert *self) {
  struct json *module = convert_get_module(self);
  return json_get(module, "alloc");
}

static struct json *convert_new_block(void) {
  struct json *json = json_new_obj();
  struct json *block = json_new_arr();
  json_insert(json, "block", block);
  json_del(block);
  return json;
}
static struct json *convert_new_instr(const char *instr) {
  struct json *json = json_new_obj();
  json_insert_str(json, "instr", instr);
  return json;
}
struct json *convert_new_alloca(struct convert *self) {
  struct json *instr = convert_new_instr("alloca");
  struct json *alloc = convert_get_alloc(self);
  json_push(alloc, instr);
  return instr;
}
static void convert_set_block(struct convert *self, struct json *block) {
  struct json *module = convert_get_module(self);
  json_insert(module, "block", block);
}
static struct json *convert_get_block(struct convert *self) {
  struct json *module = convert_get_module(self);
  return json_get(module, "block");
}

void convert_init(struct convert *self, struct json *module) {
  self->module = module;
  convert_set_block(self, json_null());
}
struct json *convert_new_module(void) {
  struct json *json = json_new_obj();
  struct json *module = json_new_arr();
  struct json *table = json_new_obj();
  json_insert(json, "module", module);
  json_insert(json, "table", table);
  json_del(table);
  json_del(module);
  return json;
}
struct json *convert_get_module(struct convert *self) {
  return self->module;
}
void convert_push_block(struct convert *self) {
  struct json *function = json_get(convert_function_get(self), "function");
  struct json *block = convert_new_block();
  json_push(function, block);
  json_del(block);
  convert_set_block(self, block);
}
struct json *convert_push_instr(struct convert *self, const char *tag) {
  struct json *block = convert_get_block(self);
  struct json *array = json_get(block, "block");
  struct json *instr = convert_new_instr(tag);
  json_push(array, instr);
  json_del(instr);
  return instr;
}
