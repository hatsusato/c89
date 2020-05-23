#include <stdio.h>

int yylex(void);
extern int num_lines;
extern int num_chars;

int main(void) {
  yylex();
  printf("lines: %d, ", num_lines);
  printf("chars: %d\n", num_chars);
  return 0;
}
