#include "ir/table.h"

#include "ast/ast_tag.h"
#include "compare.h"
#include "ir/table_type.h"
#include "map.h"
#include "map/map_type.h"
#include "sexp.h"
#include "types.h"
#include "utility.h"

struct struct_Table {
  Map *table, *labels;
};

static int table_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}
static Map *table_new_map(void) {
  Compare *cmp = compare_new(table_compare);
  Map *map = map_new(cmp);
  return map;
}

Table *table_new(void) {
  Table *table = UTILITY_MALLOC(Table);
  table->table = table_new_map();
  table->labels = table_new_map();
  return table;
}
void table_delete(Table *table) {
  map_delete(table->labels);
  map_delete(table->table);
  UTILITY_FREE(table);
}
void table_insert(Table *table, const char *key, Value *val) {
  map_insert(table->table, (ElemType)key, val);
}
Value *table_find(Table *table, const char *key) {
  ElemType *found = map_find(table->table, (ElemType)key);
  assert(found && *found);
  return *found;
}
Bool table_label_contains(Table *table, const char *label) {
  return map_contains(table->labels, (ElemType)label);
}
void table_label_insert(Table *table, const char *label, Block *block) {
  map_insert(table->labels, (ElemType)label, block);
}
Block *table_label_find(Table *table, const char *label) {
  ElemType *found = map_find(table->labels, (ElemType)label);
  assert(found && *found);
  return *found;
}
