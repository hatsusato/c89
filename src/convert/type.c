#include "type.h"

#include "json/json.h"

static struct json *convert_new_function(void) {
  struct json *json = json_new_obj();
  struct json *function = json_new_arr();
  struct json *alloc = json_new_arr();
  json_insert(json, "function", function);
  json_del(function);
  json_insert(json, "alloc", alloc);
  json_del(alloc);
  return json;
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

void convert_init(struct convert *self, struct json *module) {
  self->module = module;
  self->function = json_null();
  self->block = json_null();
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
void convert_push_function(struct convert *self) {
  struct json *module = json_get(self->module, "module");
  struct json *function = convert_new_function();
  json_push(module, function);
  json_del(function);
  self->function = function;
}
void convert_push_block(struct convert *self) {
  struct json *function = json_get(self->function, "function");
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
void convert_push_symbol(struct convert *self, struct json *identifier,
                         struct json *instruction) {
  struct json *table = json_get(self->module, "table");
  json_insert(table, json_get_str(identifier), instruction);
}
struct json *convert_lookup_symbol(struct convert *self,
                                   struct json *identifier) {
  struct json *table = json_get(self->module, "table");
  return json_get(table, json_get_str(identifier));
}
