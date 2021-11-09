#include "type.h"

#include "json/json.h"
#include "util/util.h"

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

static void convert_alloc_push(struct convert *self, struct json *instr) {
  struct json *alloc = json_get(self->function, "alloc");
  json_push(alloc, instr);
}

static void convert_table_push(struct convert *self) {
  struct json *table = json_new_obj();
  struct json *next = json_take(self->module, "table");
  json_insert(self->module, "table", table);
  json_del(table);
  json_insert(table, "$next", next);
  json_del(next);
}
static void convert_table_pop(struct convert *self) {
  struct json *table = json_get(self->module, "table");
  struct json *next = json_take(table, "$next");
  json_insert(self->module, "table", next);
  json_del(next);
}
static struct json *convert_table_insert(struct convert *self,
                                         const char *key) {
  struct json *table = json_get(self->module, "table");
  struct json *instr;
  assert(!json_has(table, key));
  instr = convert_new_instr("alloca");
  json_insert(table, key, instr);
  json_del(instr);
  return instr;
}
static struct json *convert_table_lookup(struct convert *self,
                                         const char *key) {
  struct json *table = json_get(self->module, "table");
  while (!json_is_null(table)) {
    if (json_has(table, key)) {
      return json_get(table, key);
    }
    table = json_get(table, "$next");
  }
  return json_null();
}

void convert_init(struct convert *self, struct json *module) {
  self->module = module;
  self->function = json_null();
  self->block = json_null();
  convert_table_push(self);
}
void convert_finish(struct convert *self) {
  struct json *alloc = json_get(self->function, "alloc");
  struct json *function = json_get(self->function, "function");
  struct json *front = json_front(function);
  json_append(alloc, json_get(front, "block"));
  json_insert(front, "block", alloc);
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
void convert_push_symbol(struct convert *self, struct json *identifier) {
  const char *name = json_get_str(identifier);
  struct json *instr = convert_table_insert(self, name);
  convert_alloc_push(self, instr);
}
struct json *convert_lookup_symbol(struct convert *self,
                                   struct json *identifier) {
  const char *name = json_get_str(identifier);
  return convert_table_lookup(self, name);
}
