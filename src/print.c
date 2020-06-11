#include "print.h"

#include <stdio.h>

#include "ast.h"

void print_ast(List *list) {
  while (list) {
    int tag = list_tag(list);
    switch (tag) {
    default:
      printf("[%s]\n", ast_show(tag));
    }
    list = list_next(list);
  }
}
