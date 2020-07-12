#include "table.h"

#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "set.h"
#include "utility.h"
#include "vector.h"

struct struct_SymbolTable {
  Vector *table;
};

static Bool flag_check(const void *ptr) {
  PointerBytes bytes = (PointerBytes)ptr;
  return bytes & 1;
}
static const void *flag_set(const void *ptr, Bool flag) {
  PointerBytes bytes = (PointerBytes)ptr;
  return (const void *)(bytes | (flag ? 1 : 0));
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
static void table_init(SymbolTable *table) {
  const char *builtin_types[] = {"__builtin_va_list", nil};
  const char **it = builtin_types;
  table_push(table);
  while (*it) {
    table_register(table, *it++, true);
  }
}
static void table_traverse(const SymbolTable *table, void *data,
                           Bool (*f)(const Set *, void *)) {
  const Vector *v = table->table;
  const Set **rbegin = (const Set **)vector_end(v);
  const Set **rend = (const Set **)vector_begin(v);
  const Set **it;
  for (it = rbegin; it != rend; --it) {
    if (f(it[-1], data)) {
      return;
    }
  }
}

SymbolTable *table_new(void) {
  SymbolTable *table = malloc(sizeof(SymbolTable));
  table->table = vector_new();
  table_init(table);
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
  assert(table);
  if (0 < vector_length(table->table)) {
    Set *set = (Set *)vector_back(table->table);
    if (set_contains(set, symbol)) {
      print_message(stderr, "ERROR: redeclared symbol: ");
      print_message(stderr, symbol);
      print_newline(stderr);
    } else {
      set_insert(set, flag_set(symbol, flag));
    }
  }
}
Bool table_query(const SymbolTable *table, const char *symbol) {
  assert(table);
  if (0 < vector_length(table->table)) {
    const VectorElem *it = vector_end(table->table);
    for (; it != vector_begin(table->table); --it) {
      const SetElem *elem = set_find(it[-1], symbol);
      if (elem) {
        return flag_check(*elem);
      }
    }
  }
  return false;
}
static Bool dump_foreach(const Set *set, void *data) {
  const SymbolTable *table = data;
  const char **begin = (const char **)set_begin(set);
  const char **end = (const char **)set_end(set);
  const char **it;
  (void)data;
  print_message(stderr, "----------------\n");
  for (it = begin; it != end; ++it) {
    print_message(stderr, "dump: ");
    print_message(stderr, flag_reset(*it));
    print_message(stderr, ": ");
    print_integer(stderr, flag_check(*it));
    print_newline(stderr);
    print_message(stderr, "query: ");
    print_integer(stderr, table_query(table, *it));
    print_newline(stderr);
  }
  print_message(stderr, "----------------\n");
  return false;
}
void table_dump(const SymbolTable *table) {
  if (table) {
    table_traverse(table, (void *)table, dump_foreach);
  }
}
