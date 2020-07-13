#include "table.h"

#include "register.h"
#include "set.h"
#include "symbol.h"
#include "utility.h"
#include "vector.h"

static SymbolSet *table_top(Table *table) {
  SymbolSet *top = (SymbolSet *)vector_back(table);
  assert(top);
  return top;
}

Table *table_new(void) {
  Table *table = vector_new((Destructor)set_delete);
  table_push(table);
  symbol_register(table_top(table), "__builtin_va_list", true);
  return table;
}
void table_delete(Table *table) {
  assert(table);
  vector_delete(table);
}
void table_push(Table *table) {
  assert(table);
  vector_push(table, symbol_set_new());
}
void table_pop(Table *table) {
  assert(table);
  vector_pop(table);
}
void table_register(Table *table, Sexp *ast) {
  assert(table);
  register_declaration(table_top(table), ast);
}
Bool table_query(Table *table, const char *symbol) {
  const SymbolSet **rbegin = (const SymbolSet **)vector_end(table);
  const SymbolSet **rend = (const SymbolSet **)vector_begin(table);
  const SymbolSet **it;
  for (it = rbegin; it != rend; --it) {
    const Symbol *found = symbol_query(it[-1], symbol);
    if (found) {
      return symbol_flag(found);
    }
  }
  return false;
}
