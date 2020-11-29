#include "ir/table.h"

#include "compare.h"
#include "ir/table_type.h"
#include "map.h"
#include "map/map_type.h"
#include "utility.h"

struct struct_Table {
  Map *table;
};

static int table_compare(ElemType lhs, ElemType rhs, CompareExtra extra) {
  UTILITY_UNUSED(extra);
  return utility_strcmp(lhs, rhs);
}

Table *table_new(void) {
  Table *table = UTILITY_MALLOC(Table);
  Compare *cmp = compare_new(table_compare);
  table->table = map_new(cmp);
  return table;
}
void table_delete(Table *table) {
  map_delete(table->table);
  UTILITY_FREE(table);
}
