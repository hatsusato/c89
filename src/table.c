#include "table.h"

#include <stdlib.h>

#include "vector.h"

struct struct_SymbolTable {
  Vector *table;
};

static const void *flag_set(const void *ptr) {
  PointerBytes bits = (PointerBytes)ptr;
  return (const void *)(bits | 1);
}
static const void *flag_reset(const void *ptr) {
  PointerBytes bits = (PointerBytes)ptr;
  return (const void *)(bits & ~1);
}
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
