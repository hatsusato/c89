#include "table.h"

#include "list.h"
#include "register.h"
#include "set.h"
#include "symbol.h"
#include "utility.h"
#include "vector.h"

struct struct_Table {
  Vector *vec;
  List *list;
};

static SymbolSet *table_top(Table *table) {
  SymbolSet *top = (SymbolSet *)list_at(table->list, 0);
  assert(top);
  return top;
}

Table *table_new(void) {
  Table *table = UTILITY_MALLOC(Table);
  table->vec = vector_new((Destructor)set_delete);
  table->list = list_new((Destructor)set_delete);
  table_push(table);
  symbol_register(table_top(table), "__builtin_va_list", true);
  return table;
}
void table_delete(Table *table) {
  assert(table);
  vector_delete(table->vec);
  list_delete(table->list);
  UTILITY_FREE(table);
}
void table_push(Table *table) {
  assert(table);
  vector_push(table->vec, symbol_set_new());
  list_insert(table->list, symbol_set_new());
}
void table_pop(Table *table) {
  assert(table);
  vector_pop(table->vec);
  list_remove(table->list);
}
void table_register(Table *table, Sexp *ast) {
  assert(table);
  register_declaration(table_top(table), ast);
}
typedef struct {
  const char *symbol;
  const Symbol *found;
} TableQuery;
static void table_query_map(ElemType elem, void *data) {
  const SymbolSet *set = elem;
  TableQuery *query = data;
  if (!query->found) {
    query->found = symbol_query(set, query->symbol);
  }
}
Bool table_query(Table *table, const char *symbol) {
  TableQuery query = {NULL, NULL};
  query.symbol = symbol;
  list_map(table->list, &query, table_query_map);
  return query.found ? symbol_flag(query.found) : false;
}
