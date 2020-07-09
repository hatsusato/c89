#include "table.h"

#include <stdlib.h>

#include "vector.h"

struct struct_SymbolTable {
  Vector *table;
};

SymbolTable *table_new(void) {
  SymbolTable *table = malloc(sizeof(SymbolTable));
  table->table = vector_new();
  return table;
}
void table_delete(SymbolTable *table) {
  vector_delete(table->table);
  free(table);
}
void table_push(SymbolTable *table) {
  assert(table);
  vector_push(table->table, nil);
}
void table_pop(SymbolTable *table) {
  assert(table);
  vector_pop(table->table, nil);
}
