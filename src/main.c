#include <stdio.h>

#include "parser.tab.h"
int g_result;

void yyerror(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}

const char* show_token(int token) {
#define CASE_TOKEN(t) \
  case t:             \
    return #t
  switch (token) {
    CASE_TOKEN(NUM);
    CASE_TOKEN(PLUS);
    CASE_TOKEN(MINUS);
    CASE_TOKEN(ASTER);
    CASE_TOKEN(SLASH);
    CASE_TOKEN(LPAR);
    CASE_TOKEN(RPAR);
    CASE_TOKEN(NL);
  default:
    fprintf(stderr, "unknown: %d\n", token);
    return "UNKNOWN";
  }
#undef CASE_TOKEN
}

int main(void) {
  int token = 0;
  while (0 != (token = yylex())) {
    printf("%s\n", show_token(token));
  }
  return 0;
}
