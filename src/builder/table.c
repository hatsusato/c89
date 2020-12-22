#include "table.h"

#include "compare.h"
#include "instruction.h"
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
void table_push(Table *table) {
  Map *map = table_new_map();
  vector_push(table->stack, map);
}
void table_pop(Table *table) {
  vector_pop(table->stack);
}
void table_insert(Table *table, const char *key, Instruction *val) {
  Map *map = vector_back(table->stack);
  UTILITY_ASSERT(map);
  UTILITY_ASSERT(INSTRUCTION_ALLOCA == instruction_kind(val));
  map_insert(map, (ElemType)key, val);
}
Instruction *table_find(Table *table, const char *key) {
  ElemType *begin = vector_begin(table->stack);
  ElemType *end = vector_end(table->stack);
  while (begin < end--) {
    ElemType *found = map_find(*end, (ElemType)key);
    if (found) {
      UTILITY_ASSERT(*found);
      UTILITY_ASSERT(INSTRUCTION_ALLOCA == instruction_kind(*found));
      return *found;
    }
  }
  UTILITY_ASSERT(0);
  return NULL;
}
void table_builtin_insert(Table *table, const char *key, Instruction *val) {
  UTILITY_ASSERT(INSTRUCTION_ALLOCA == instruction_kind(val));
  map_insert(table->table, (ElemType)key, val);
}
Instruction *table_builtin_find(Table *table, const char *key) {
  ElemType *found = map_find(table->table, (ElemType)key);
  UTILITY_ASSERT(found && *found);
  UTILITY_ASSERT(INSTRUCTION_ALLOCA == instruction_kind(*found));
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
