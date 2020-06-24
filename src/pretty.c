#include "pretty.h"

#include <assert.h>
#include <stdio.h>

#include "ast.h"
#include "print.h"
#include "utility.h"

typedef struct {
  List *head, *tail;
} Pretty;

static List *pretty_convert(Pretty *pretty, List *ast, int indent);

static void pretty_push(Pretty *pretty, int tag, void *data) {
  if (pretty->tail) {
    list_insert(pretty->tail, list_new(tag, data));
    pretty->tail = list_next(pretty->tail);
  } else {
    pretty->head = pretty->tail = list_new(tag, data);
  }
}
static void pretty_push_tag(Pretty *pretty, int tag) {
  pretty_push(pretty, tag, nil);
}
static void pretty_push_indent(Pretty *pretty, int indent) {
  for (; 0 < indent; --indent) {
    pretty_push_tag(pretty, AST_TAB);
  }
}
static List *pretty_convert_token(Pretty *pretty, List *ast) {
  ast = list_next(ast);
  pretty_push(pretty, list_tag(ast), list_data(ast));
  return list_next(ast);
}
static List *pretty_convert_list(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  int delim = AST_NIL;
  ast = list_next(ast);
  switch (tag) {
  case AST_TRANSLATION_UNIT:
    delim = AST_NEWLINE;
    break;
  case AST_ARGUMENT_EXPRESSION_LIST:
  case AST_INIT_DECLARATOR_LIST:
  case AST_STRUCT_DECLARATOR_LIST:
  case AST_ENUMERATOR_LIST:
  case AST_PARAMETER_LIST:
  case AST_IDENTIFIER_LIST:
  case AST_INITIALIZER_LIST:
    delim = AST_COMMA;
    break;
  case AST_DECLARATION_SPECIFIERS:
  case AST_STRUCT_DECLARATION_LIST:
  case AST_SPECIFIER_QUALIFIER_LIST:
  case AST_TYPE_QUALIFIER_LIST:
  case AST_DECLARATION_LIST:
  case AST_STATEMENT_LIST:
    break;
  default:
    assert(0);
    return ast;
  }
  if (AST_NIL != list_tag(ast)) {
    ast = pretty_convert(pretty, ast, indent);
  }
  while (AST_NIL != list_tag(ast)) {
    if (AST_NIL != delim) {
      pretty_push_tag(pretty, delim);
    }
    ast = pretty_convert(pretty, ast, indent);
  }
  return list_next(ast);
}
static List *pretty_convert_arity0(Pretty *pretty, List *ast) {
  pretty_push_tag(pretty, list_tag(ast));
  return list_next(ast);
}
static List *pretty_convert_arity1(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_PRIMARY_EXPRESSION:
  case AST_CALL:
  case AST_SIZEOF:
  case AST_DIRECT_DECLARATOR:
  case AST_OLD:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    return ast;
  case AST_ARRAY:
    pretty_push_tag(pretty, AST_LEFT_BRACKET);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_BRACKET);
    return ast;
  case AST_PERIOD:
  case AST_ARROW:
    pretty_push_tag(pretty, tag);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_UNARY_EXPRESSION:
    pretty_push_tag(pretty, AST_SIZEOF);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_DECLARATION:
  case AST_EXPRESSION_STATEMENT:
  case AST_JUMP_STATEMENT:
    pretty_push_indent(pretty, indent);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_SEMICOLON);
    pretty_push_tag(pretty, AST_NEWLINE);
    return ast;
  case AST_ENUM_SPECIFIER:
    pretty_push_tag(pretty, AST_ENUM);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_POINTER:
    pretty_push_tag(pretty, AST_ASTERISK);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_PARAMETER_TYPE_LIST:
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_COMMA);
    pretty_push_tag(pretty, AST_ELLIPSIS);
    return ast;
  case AST_INITIALIZER:
    pretty_push_tag(pretty, AST_LEFT_BRACE);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_BRACE);
    return ast;
  case AST_SELECTION_STATEMENT:
  case AST_ITERATION_STATEMENT:
    pretty_push_indent(pretty, indent);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_NEWLINE);
    return ast;
  case AST_CASE:
  case AST_GOTO:
  case AST_RETURN:
    pretty_push_tag(pretty, tag);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_CONSTANT_EXPRESSION:
  case AST_INIT_DECLARATOR:
  case AST_STORAGE_CLASS_SPECIFIER:
  case AST_TYPE_SPECIFIER:
  case AST_STRUCT_DECLARATOR:
  case AST_ENUMERATOR:
  case AST_TYPE_QUALIFIER:
  case AST_DECLARATOR:
  case AST_PARAMETER_DECLARATION:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_TYPEDEF_NAME:
  case AST_STATEMENT:
  case AST_EXTERNAL_DECLARATION:
  case AST_FUNCTION_DEFINITION:
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  default:
    assert(0);
    return ast;
  }
}
static List *pretty_convert_arity2(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_CAST_EXPRESSION:
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_DECLARATION:
  case AST_STRUCT_DECLARATION:
    pretty_push_indent(pretty, indent);
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_SEMICOLON);
    pretty_push_tag(pretty, AST_NEWLINE);
    return ast;
  case AST_INIT_DECLARATOR:
  case AST_ENUMERATOR:
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_ASSIGN);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_STRUCT_DECLARATOR:
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_COLON);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_ENUM_SPECIFIER:
    pretty_push_tag(pretty, AST_ENUM);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_BLANK);
    pretty_push_tag(pretty, AST_LEFT_BRACE);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_BRACE);
    return ast;
  case AST_POINTER:
    pretty_push_tag(pretty, AST_ASTERISK);
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_LABELED_STATEMENT:
    pretty_push_indent(pretty, indent - 1);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_COLON);
    pretty_push_tag(pretty, AST_NEWLINE);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_COMPOUND_STATEMENT:
    pretty_push_tag(pretty, AST_LEFT_BRACE);
    pretty_push_tag(pretty, AST_NEWLINE);
    ast = pretty_convert(pretty, ast, indent + 1);
    ast = pretty_convert(pretty, ast, indent + 1);
    pretty_push_indent(pretty, indent);
    pretty_push_tag(pretty, AST_RIGHT_BRACE);
    return ast;
  case AST_IF:
  case AST_SWITCH:
  case AST_WHILE:
    pretty_push_tag(pretty, tag);
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_DO:
    pretty_push_tag(pretty, tag);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_BLANK);
    pretty_push_tag(pretty, AST_WHILE);
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    pretty_push_tag(pretty, AST_SEMICOLON);
    return ast;
  case AST_POSTFIX_EXPRESSION:
  case AST_UNARY_EXPRESSION:
  case AST_STRUCT_OR_UNION_SPECIFIER:
  case AST_DECLARATOR:
  case AST_DIRECT_DECLARATOR:
  case AST_TYPE_NAME:
  case AST_ABSTRACT_DECLARATOR:
  case AST_PARAMETER_DECLARATION:
  case AST_DIRECT_ABSTRACT_DECLARATOR:
  case AST_OLD:
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  default:
    assert(0);
    return ast;
  }
}
static List *pretty_convert_arity3(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_BINARY: {
    int op = 0;
    assert(AST_ARITY0 == list_tag(ast));
    ast = list_next(ast);
    op = list_tag(ast);
    ast = list_next(ast);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, op);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  }
  case AST_CONDITIONAL_EXPRESSION:
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_QUESTION);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_COLON);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_STRUCT_OR_UNION_SPECIFIER:
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_BLANK);
    pretty_push_tag(pretty, AST_LEFT_BRACE);
    pretty_push_tag(pretty, AST_NEWLINE);
    ast = pretty_convert(pretty, ast, indent + 1);
    pretty_push_indent(pretty, indent);
    pretty_push_tag(pretty, AST_RIGHT_BRACE);
    return ast;
  case AST_IF:
    pretty_push_tag(pretty, tag);
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_BLANK);
    pretty_push_tag(pretty, AST_ELSE);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_FUNCTION_DEFINITION:
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_OLD:
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  default:
    assert(0);
    return ast;
  }
}
static List *pretty_convert_arity4(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_FOR:
    pretty_push_tag(pretty, tag);
    pretty_push_tag(pretty, AST_LEFT_PAREN);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_SEMICOLON);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_SEMICOLON);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    pretty_push_tag(pretty, AST_RIGHT_PAREN);
    pretty_push_tag(pretty, AST_BLANK);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  case AST_OLD:
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    ast = pretty_convert(pretty, ast, indent);
    return ast;
  default:
    assert(0);
    return ast;
  }
}
static List *pretty_convert(Pretty *pretty, List *ast, int indent) {
  int tag = list_tag(ast);
  ast = list_next(ast);
  switch (tag) {
  case AST_TOKEN:
    return pretty_convert_token(pretty, ast);
  case AST_LIST:
    return pretty_convert_list(pretty, ast, indent);
  case AST_ARITY0:
    return pretty_convert_arity0(pretty, ast);
  case AST_ARITY1:
    return pretty_convert_arity1(pretty, ast, indent);
  case AST_ARITY2:
    return pretty_convert_arity2(pretty, ast, indent);
  case AST_ARITY3:
    return pretty_convert_arity3(pretty, ast, indent);
  case AST_ARITY4:
    return pretty_convert_arity4(pretty, ast, indent);
  default:
    assert(0);
    return ast;
  }
}
static void pretty_print_ast(List *ast) {
  int tag = list_tag(ast);
  switch (tag) {
  case AST_BLANK:
    printf(" ");
    break;
  case AST_TAB:
    printf("  ");
    break;
  case AST_NEWLINE:
    printf("\n");
    break;
  case AST_DATA:
    print_data(ast);
    break;
  case AST_SLASH:
  case AST_PERCENT:
  case AST_LEFT_SHIFT:
  case AST_RIGHT_SHIFT:
  case AST_LESS_THAN:
  case AST_GREATER_THAN:
  case AST_LESS_EQUAL:
  case AST_GREATER_EQUAL:
  case AST_EQUAL:
  case AST_NOT_EQUAL:
  case AST_CARET:
  case AST_BAR:
  case AST_AND:
  case AST_OR:
  case AST_QUESTION:
  case AST_ASSIGN:
  case AST_ASTERISK_ASSIGN:
  case AST_SLASH_ASSIGN:
  case AST_PERCENT_ASSIGN:
  case AST_PLUS_ASSIGN:
  case AST_MINUS_ASSIGN:
  case AST_LEFT_SHIFT_ASSIGN:
  case AST_RIGHT_SHIFT_ASSIGN:
  case AST_AMPERSAND_ASSIGN:
  case AST_CARET_ASSIGN:
  case AST_BAR_ASSIGN:
  case AST_COLON:
    printf(" %s ", ast_show(tag));
    break;
  case AST_COMMA:
#define HANDLE(name, str) case AST_##name:
#include "enum/keyword.def"
#undef HANDLE
    printf("%s ", ast_show(tag));
    break;
  default:
    printf("%s", ast_show(tag));
    break;
  }
}

List *pretty_print(List *ast, int indent) {
  Pretty pretty = {nil, nil};
  ast = pretty_convert(&pretty, ast, indent);
  assert(!ast);
  ast = pretty.head;
  while (ast) {
    pretty_print_ast(ast);
    ast = list_next(ast);
  }
  list_delete(pretty.head, nil);
  return ast;
}
