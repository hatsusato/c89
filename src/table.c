#include "table.h"

#include "set.h"
#include "symbols.h"
#include "utility.h"
#include "vector.h"

Table *table_new(void) {
  return vector_new((Destructor)set_delete);
}
void table_delete(Table *table) {
  assert(table);
  vector_delete(table);
}
void table_push(Table *table) {
  assert(table);
  vector_push(table, set_new((Destructor)symbol_delete, symbol_compare));
}
void table_pop(Table *table) {
  assert(table);
  vector_pop(table);
}
