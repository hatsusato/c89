#include "type.h"

#include "json/json.h"

static struct json *convert_new_function(void) {
  struct json *function = json_new_obj();
  struct json *blocks = json_new_arr();
  json_insert(function, "function", blocks);
  json_del(blocks);
  return function;
}
static struct json *convert_new_block(void) {
  struct json *block = json_new_obj();
  struct json *instructions = json_new_arr();
  json_insert(block, "block", instructions);
  json_del(instructions);
  return block;
}
static struct json *convert_new_instr(const char *tag) {
  struct json *instr = json_new_obj();
  json_insert_str(instr, "instr", tag);
  return instr;
}
static void convert_push_function(struct convert *self) {
  struct json *module = json_get(self->module, "module");
  struct json *function = convert_new_function();
  json_push(module, function);
  json_del(function);
  self->function = function;
}

struct json *convert_extra_new_module(void) {
  struct json *module = json_new_obj();
  struct json *functions = json_new_arr();
  struct json *table = json_new_obj();
  json_insert(module, "module", functions);
  json_insert(module, "table", table);
  json_del(table);
  json_del(functions);
  return module;
}
void convert_init(struct convert *self, struct json *module) {
  self->module = module;
  self->function = json_null();
  self->block = json_null();
  convert_push_function(self);
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
