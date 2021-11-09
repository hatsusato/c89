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

void convert_init(struct convert *self, struct json *module) {
  self->module = module;
  self->block = json_null();
  convert_table_push(self);
}
void convert_finish(struct convert *self) {
  convert_function_finish(self);
  convert_table_pop(self);
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
  self->block = block;
}
struct json *convert_push_instr(struct convert *self, const char *tag) {
  struct json *block = json_get(self->block, "block");
  struct json *instr = convert_new_instr(tag);
  json_push(block, instr);
  json_del(instr);
  return instr;
}
