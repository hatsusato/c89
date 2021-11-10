#include "numbering.h"

#include "json/json.h"
#include "json/map.h"
#include "util/util.h"

static bool_t generate_numbering_has_register(struct json *json) {
  const char *tag = json_get_str(json_get(json, "instr"));
  return !(util_streq(tag, "store") || util_streq(tag, "ret"));
}
static void generate_numbering_instr(struct json_map *map) {
  index_t *index = json_map_extra(map);
  struct json *instr = json_map_val(map);
  if (generate_numbering_has_register(instr)) {
    struct json *reg = json_new_int((*index)++);
    json_insert(instr, "reg", reg);
    json_del(reg);
  }
}
static void generate_numbering_block(struct json_map *map) {
  index_t *index = json_map_extra(map);
  struct json *block = json_map_val(map);
  struct json *label = json_new_int((*index)++);
  json_insert(block, "label", label);
  json_del(label);
  json_foreach(json_get(block, "instructions"), generate_numbering_instr,
               index);
}

void generate_numbering(struct json *function) {
  struct json *blocks = json_get(function, "function");
  index_t index = 0;
  json_foreach(blocks, generate_numbering_block, &index);
}
