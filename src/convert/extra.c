#include "extra.h"

#include "json/json.h"

static struct json *convert_extra_new_function(void) {
  struct json *function = json_new_obj();
  struct json *blocks = json_new_arr();
  json_insert(function, "function", blocks);
  json_del(blocks);
  return function;
}
static struct json *convert_extra_new_block(void) {
  struct json *block = json_new_obj();
  struct json *instructions = json_new_arr();
  json_insert(block, "block", instructions);
  json_del(instructions);
  return block;
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
struct json *convert_extra_new_instr(const char *tag) {
  struct json *instr = json_new_obj();
  json_insert_str(instr, "instr", tag);
  return instr;
}
void convert_extra_init(struct convert_extra *self, struct json *module) {
  struct json *function = convert_extra_new_function();
  self->module = module;
  self->function = function;
  self->block = json_null();
  json_push(json_get(module, "module"), function);
  json_del(function);
}
void convert_extra_push_block(struct convert_extra *self) {
  struct json *block = convert_extra_new_block();
  self->block = block;
  json_push(json_get(self->function, "function"), block);
  json_del(block);
}
void convert_extra_push_instr(struct convert_extra *self, struct json *instr) {
  json_push(json_get(self->block, "block"), instr);
}
void convert_extra_push_symbol(struct convert_extra *self,
                               struct json *identifier,
                               struct json *instruction) {
  struct json *table = json_get(self->module, "table");
  json_insert(table, json_get_str(identifier), instruction);
}
