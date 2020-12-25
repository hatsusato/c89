#include "table.h"

#include "compare.h"
#include "instruction.h"
#include "map.h"
#include "utility.h"
#include "vector.h"

struct struct_Table {
  Map *global;
  Vector *stack;
  Map *labels;
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
  table->global = table_new_map();
  table->stack = vector_new(table_delete_map);
  table->labels = table_new_map();
  return table;
}
void table_delete(Table *table) {
  map_delete(table->labels);
  vector_delete(table->stack);
  map_delete(table->global);
  UTILITY_FREE(table);
}
void table_clear(Table *table) {
  UTILITY_ASSERT(vector_empty(table->stack));
  map_clear(table->labels);
}
void table_push(Table *table) {
  Map *map = table_new_map();
  vector_push(table->stack, map);
}
void table_pop(Table *table) {
  vector_pop(table->stack);
}
void table_insert(Table *table, const char *key, Instruction *val) {
  UTILITY_ASSERT(!vector_empty(table->stack));
  map_insert(vector_back(table->stack), (ElemType)key, val);
}
Value *table_find(Table *table, const char *key) {
  ElemType *found;
  ElemType *begin = vector_begin(table->stack);
  ElemType *end = vector_end(table->stack);
  while (begin < end--) {
    ElemType *found = map_find(*end, (ElemType)key);
    if (found) {
      return *found;
    }
  }
  found = map_find(table->global, (ElemType)key);
  return found ? *found : found;
}
void table_label_insert(Table *table, const char *label, Block *block) {
  map_insert(table->labels, (ElemType)label, block);
}
Block *table_label_find(Table *table, const char *label) {
  ElemType *found = map_find(table->labels, (ElemType)label);
  return found ? *found : found;
}
