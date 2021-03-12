#include "table.h"

#include "instruction.h"
#include "map/map.h"
#include "utility/utility.h"
#include "vector/vector.h"

struct struct_Table {
  Map *global;
  Vector *stack;
  Map *labels;
};

static void table_delete_map(VectorElem map) {
  map_delete(map);
}

Table *table_new(void) {
  Table *table = UTILITY_MALLOC(Table);
  table->global = map_new(NULL);
  table->stack = vector_new(table_delete_map);
  table->labels = map_new(NULL);
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
  Map *map = map_new(NULL);
  vector_push(table->stack, map);
}
void table_pop(Table *table) {
  vector_pop(table->stack);
}
void table_insert_global(Table *table, const char *key, Global *val) {
  map_insert(table->global, key, val);
}
void table_insert_local(Table *table, const char *key, Instruction *val) {
  UTILITY_ASSERT(!vector_empty(table->stack));
  map_insert(vector_back(table->stack), key, val);
}
Value *table_find(Table *table, const char *key, Module *module) {
  CompareElem *found;
  VectorElem *begin = vector_begin(table->stack);
  VectorElem *end = vector_end(table->stack);
  while (begin < end--) {
    found = map_find(*end, key);
    if (found) {
      return (Value *)*found;
    }
  }
  found = map_find(table->global, key);
  if (found) {
    module_insert_prior(module, (Global *)*found);
    return (Value *)*found;
  }
  return NULL;
}
void table_label_insert(Table *table, const char *label, Block *block) {
  map_insert(table->labels, label, block);
}
Block *table_label_find(Table *table, const char *label) {
  CompareElem *found = map_find(table->labels, label);
  return (Block *)(found ? *found : found);
}
