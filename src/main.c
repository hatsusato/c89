#include "pretty.h"
#include "print.h"
#include "result.h"

void print_seq(Result *result) {
  Sexp *sexp = result_set_sexp(result, nil);
  print_ast(sexp);
  pretty_print(sexp);
  result_set_sexp(result, sexp);
}

int main(void) {
  Result *result = result_new();
  int ret = result_parse(result);
  if (0 == ret) {
    print_seq(result);
  }
  result_delete(result);
  return ret;
}
