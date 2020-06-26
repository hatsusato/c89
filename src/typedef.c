#include "typedef.h"

#include "list.h"
#include "scanner.h"
#include "string.h"
#include "utility.h"

static List *typedef_insert(yyscan_t scanner, List *ast) {
  assert(AST_DATA == list_tag(ast));
  scanner_insert_symbol(scanner, string_begin(list_data(ast)));
  return list_next(ast);
}
static List *typedef_next(List *ast, int tag) {
  assert(tag == list_tag(ast));
  return list_next(ast);
}
