#include "table.h"

#include "set.h"
#include "vector.h"

Table *table_new(void) {
  return vector_new((Destructor)set_delete);
}
void table_delete(Table *table) {
  vector_delete(table);
}
