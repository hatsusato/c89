#include "table.h"

#include <stdlib.h>
#include <string.h>

#include "set.h"
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
static int compare(const void *lhs, const void *rhs) {
  const char *const *l = lhs;
  const char *const *r = rhs;
  return strcmp(flag_reset(*l), flag_reset(*r));
}
static void destructor(const void *set) {
  set_delete((Set *)set);
}

SymbolTable *table_new(void) {
  SymbolTable *table = malloc(sizeof(SymbolTable));
  table->table = vector_new();
  return table;
}
void table_delete(SymbolTable *table) {
  vector_clear(table->table, destructor);
  vector_delete(table->table);
  free(table);
}
void table_push(SymbolTable *table) {
  assert(table);
  vector_push(table->table, set_new(compare));
}
void table_pop(SymbolTable *table) {
  assert(table);
  vector_pop(table->table, destructor);
}
