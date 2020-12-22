#include "table.h"

#include "compare.h"
#include "map.h"
#include "utility.h"
#include "vector.h"

struct struct_Table {
  Vector *stack;
  Map *table, *labels;
};

static Map *table_new_map(void) {
  Compare *cmp = compare_new_strcmp();
  Map *map = map_new(cmp);
  return map;
}
static void table_delete_map(ElemType map) {
  map_delete(map);
}

Table *table_new(void) {
  Table *table = UTILITY_MALLOC(Table);
  table->stack = vector_new(table_delete_map);
  table->table = table_new_map();
  table->labels = table_new_map();
  return table;
}
void table_delete(Table *table) {
  map_delete(table->labels);
  map_delete(table->table);
  vector_delete(table->stack);
  UTILITY_FREE(table);
}
void table_insert(Table *table, const char *key, Value *val) {
  map_insert(table->table, (ElemType)key, val);
}
Value *table_find(Table *table, const char *key) {
  ElemType *found = map_find(table->table, (ElemType)key);
  UTILITY_ASSERT(found && *found);
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
  UTILITY_ASSERT(found && *found);
  return *found;
}
