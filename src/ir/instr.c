#include "instr.h"

#include "json/json.h"
#include "util/symbol.h"
#include "util/util.h"

struct json *ir_instr_new(const char *tag) {
  struct json *instr = json_new_obj();
  json_insert(instr, tag, json_null());
  return instr;
}
void ir_instr_insert(struct json *instr, const char *key, struct json *value) {
  json_set(instr, key, json_new_weak(value));
}
void ir_instr_icmp_cond(struct json *instr, struct json *value) {
  struct json *zero = json_new_obj();
  json_set(zero, SYMBOL_IMMEDIATE, json_new_int(0));
  json_insert(instr, "lhs", value);
  json_insert(instr, "rhs", zero);
  json_del(zero);
}
bool_t ir_instr_check_kind(struct json *instr, const char *tag) {
  return json_has(instr, tag);
}
void ir_instr_set_skip(struct json *instr) {
  json_insert(instr, "skip", json_null());
}
bool_t ir_instr_is_skip(struct json *instr) {
  return json_has(instr, "skip");
}
void ir_instr_set_numbering(struct json *instr, int num) {
  assert(!ir_instr_has_numbering(instr));
  json_set(instr, "reg", json_new_int(num));
}
bool_t ir_instr_has_numbering(struct json *instr) {
  return json_has(instr, "reg");
}
int ir_instr_get_numbering(struct json *instr) {
  struct json *reg = json_get(instr, "reg");
  assert(json_is_int(reg));
  return json_int_get(reg);
}
