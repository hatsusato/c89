#include "table.h"

#include <stdlib.h>
#include <string.h>

#include "set.h"
#include "vector.h"

struct struct_SymbolTable {
  Vector *table;
};

static Bool flag_check(const void *ptr) {
  PointerBytes bytes = (PointerBytes)ptr;
  return bytes & 1;
}
static const void *flag_set(const void *ptr) {
  PointerBytes bytes = (PointerBytes)ptr;
  return (const void *)(bytes | 1);
}
static const void *flag_reset(const void *ptr) {
  PointerBytes bytes = (PointerBytes)ptr;
  return (const void *)(bytes & ~1);
}
static int compare(const SetElem *lhs, const SetElem *rhs) {
  return strcmp(flag_reset(*lhs), flag_reset(*rhs));
}
static void destructor(const void *set) {
  set_delete((Set *)set);
}
static Set *table_set(SymbolTable *table) {
  assert(table);
  return (Set *)vector_back(table->table);
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
void table_register(SymbolTable *table, const char *symbol, Bool flag) {
  Set *set = table_set(table);
  set_insert(set, flag ? flag_set(symbol) : symbol);
}
Bool table_query(SymbolTable *table, const char *symbol) {
  Set *set = table_set(table);
  return set_contains(set, symbol);
}
