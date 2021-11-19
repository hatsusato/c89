#ifndef INCLUDE_GUARD_E0353946_9774_492C_A775_4B26998B01E8
#define INCLUDE_GUARD_E0353946_9774_492C_A775_4B26998B01E8

/* 6.1 Lexical elements */
/* 6.1.1 Keywords */
#define SYMBOL_AUTO "auto"
#define SYMBOL_BREAK "break"
#define SYMBOL_CASE "case"
#define SYMBOL_CHAR "char"
#define SYMBOL_CONST "const"
#define SYMBOL_CONTINUE "continue"
#define SYMBOL_DEFAULT "default"
#define SYMBOL_DO "do"
#define SYMBOL_DOUBLE "double"
#define SYMBOL_ELSE "else"
#define SYMBOL_ENUM "enum"
#define SYMBOL_EXTERN "extern"
#define SYMBOL_FLOAT "float"
#define SYMBOL_FOR "for"
#define SYMBOL_GOTO "goto"
#define SYMBOL_IF "if"
#define SYMBOL_INT "int"
#define SYMBOL_LONG "long"
#define SYMBOL_REGISTER "register"
#define SYMBOL_RETURN "return"
#define SYMBOL_SHORT "short"
#define SYMBOL_SIGNED "signed"
#define SYMBOL_SIZEOF "sizeof"
#define SYMBOL_STATIC "static"
#define SYMBOL_STRUCT "struct"
#define SYMBOL_SWITCH "switch"
#define SYMBOL_TYPEDEF "typedef"
#define SYMBOL_UNION "union"
#define SYMBOL_UNSIGNED "unsigned"
#define SYMBOL_VOID "void"
#define SYMBOL_VOLATILE "volatile"
#define SYMBOL_WHILE "while"
/* 6.1.2 Identifiers */
#define SYMBOL_IDENTIFIER "identifier"
#define SYMBOL_TYPEDEF_IDENTIFIER "typedef-identifier"
/* 6.1.3 Constants */
#define SYMBOL_FLOATING_CONSTANT "floating-constant"
#define SYMBOL_INTEGER_CONSTANT "integer-constant"
#define SYMBOL_ENUMERATION_CONSTANT "enumeration-constant"
#define SYMBOL_CHARACTER_CONSTANT "character-constant"
/* 6.1.4 String literals */
#define SYMBOL_STRING_LITERAL "string-literal"
/* 6.1.5 Operators */
#define SYMBOL_PERIOD "."
#define SYMBOL_ARROW "->"
#define SYMBOL_INCREMENT "++"
#define SYMBOL_DECREMENT "--"
#define SYMBOL_AMPERSAND "&"
#define SYMBOL_ASTERISK "*"
#define SYMBOL_PLUS "+"
#define SYMBOL_MINUS "-"
#define SYMBOL_TILDE "~"
#define SYMBOL_EXCLAMATION "!"
#define SYMBOL_SLASH "/"
#define SYMBOL_PERCENT "%"
#define SYMBOL_LEFT_SHIFT "<<"
#define SYMBOL_RIGHT_SHIFT ">>"
#define SYMBOL_LESS_THAN "<"
#define SYMBOL_GREATER_THAN ">"
#define SYMBOL_LESS_EQUAL "<="
#define SYMBOL_GREATER_EQUAL ">="
#define SYMBOL_EQUAL "=="
#define SYMBOL_NOT_EQUAL "!="
#define SYMBOL_CARET "^"
#define SYMBOL_BAR "|"
#define SYMBOL_AND "&&"
#define SYMBOL_OR "||"
#define SYMBOL_QUESTION "?"
#define SYMBOL_ASSIGN "="
#define SYMBOL_ASTERISK_ASSIGN "*="
#define SYMBOL_SLASH_ASSIGN "/="
#define SYMBOL_PERCENT_ASSIGN "%="
#define SYMBOL_PLUS_ASSIGN "+="
#define SYMBOL_MINUS_ASSIGN "-="
#define SYMBOL_LEFT_SHIFT_ASSIGN "<<="
#define SYMBOL_RIGHT_SHIFT_ASSIGN ">>="
#define SYMBOL_AMPERSAND_ASSIGN "&="
#define SYMBOL_CARET_ASSIGN "^="
#define SYMBOL_BAR_ASSIGN "|="
/* 6.1.6 Punctuators */
#define SYMBOL_LEFT_BRACKET "["
#define SYMBOL_RIGHT_BRACKET "]"
#define SYMBOL_LEFT_PAREN "("
#define SYMBOL_RIGHT_PAREN ")"
#define SYMBOL_LEFT_BRACE "{"
#define SYMBOL_RIGHT_BRACE "}"
#define SYMBOL_COMMA ","
#define SYMBOL_COLON ":"
#define SYMBOL_SEMICOLON ";"
#define SYMBOL_ELLIPSIS "..."

/* 6.3 Expressions */
#define SYMBOL_PRIMARY_EXPRESSION "primary-expression"
#define SYMBOL_POSTFIX_EXPRESSION "postfix-expression"
#define SYMBOL_ARGUMENT_EXPRESSION_LIST "argument-expression-list"
#define SYMBOL_UNARY_EXPRESSION "unary-expression"
#define SYMBOL_UNARY_OPERATOR "unary-operator"
#define SYMBOL_CAST_EXPRESSION "cast-expression"
#define SYMBOL_MULTIPLICATIVE_EXPRESSION "multiplicative-expression"
#define SYMBOL_ADDITIVE_EXPRESSION "additive-expression"
#define SYMBOL_SHIFT_EXPRESSION "shift-expression"
#define SYMBOL_RELATIONAL_EXPRESSION "relational-expression"
#define SYMBOL_EQUALITY_EXPRESSION "equality-expression"
#define SYMBOL_AND_EXPRESSION "and-expression"
#define SYMBOL_EXCLUSIVE_OR_EXPRESSION "exclusive-or-expression"
#define SYMBOL_INCLUSIVE_OR_EXPRESSION "inclusive-or-expression"
#define SYMBOL_LOGICAL_AND_EXPRESSION "logical-and-expression"
#define SYMBOL_LOGICAL_OR_EXPRESSION "logical-or-expression"
#define SYMBOL_CONDITIONAL_EXPRESSION "conditional-expression"
#define SYMBOL_ASSIGNMENT_EXPRESSION "assignment-expression"
#define SYMBOL_ASSIGNMENT_OPERATOR "assignment-operator"
#define SYMBOL_EXPRESSION "expression"

/* 6.4 Constant expressions */
#define SYMBOL_CONSTANT_EXPRESSION "constant-expression"

/* 6.5 Declarations */
#define SYMBOL_DECLARATION "declaration"
#define SYMBOL_DECLARATION_SPECIFIERS "declaration-specifiers"
#define SYMBOL_INIT_DECLARATOR_LIST "init-declarator-list"
#define SYMBOL_INIT_DECLARATOR "init-declarator"
#define SYMBOL_STORAGE_CLASS_SPECIFIER "storage-class-specifier"
#define SYMBOL_TYPE_SPECIFIER "type-specifier"
#define SYMBOL_STRUCT_OR_UNION_SPECIFIER "struct-or-union-specifier"
#define SYMBOL_STRUCT_OR_UNION "struct-or-union"
#define SYMBOL_STRUCT_DECLARATION_LIST "struct-declaration-list"
#define SYMBOL_STRUCT_DECLARATION "struct-declaration"
#define SYMBOL_SPECIFIER_QUALIFIER_LIST "specifier-qualifier-list"
#define SYMBOL_SPECIFIER_QUALIFIER "specifier-qualifier"
#define SYMBOL_STRUCT_DECLARATOR_LIST "struct-declarator-list"
#define SYMBOL_STRUCT_DECLARATOR "struct-declarator"
#define SYMBOL_ENUM_SPECIFIER "enum-specifier"
#define SYMBOL_ENUMERATOR_LIST "enumerator-list"
#define SYMBOL_ENUMERATOR "enumerator"
#define SYMBOL_TYPE_QUALIFIER "type-qualifier"
#define SYMBOL_DECLARATOR "declarator"
#define SYMBOL_DIRECT_DECLARATOR "direct-declarator"
#define SYMBOL_POINTER "pointer"
#define SYMBOL_TYPE_QUALIFIER_LIST "type-qualifier-list"
#define SYMBOL_PARAMETER_TYPE_LIST "parameter-type-list"
#define SYMBOL_PARAMETER_LIST "parameter-list"
#define SYMBOL_PARAMETER_DECLARATION "parameter-declaration"
#define SYMBOL_IDENTIFIER_LIST "identifier-list"
#define SYMBOL_TYPE_NAME "type-name"
#define SYMBOL_ABSTRACT_DECLARATOR "abstract-declarator"
#define SYMBOL_DIRECT_ABSTRACT_DECLARATOR "direct-abstract-declarator"
#define SYMBOL_TYPEDEF_NAME "typedef-name"
#define SYMBOL_INITIALIZER "initializer"
#define SYMBOL_INITIALIZER_LIST "initializer-list"

/* 6.6 Statements */
#define SYMBOL_STATEMENT "statement"
#define SYMBOL_LABELED_STATEMENT "labeled-statement"
#define SYMBOL_COMPOUND_STATEMENT "compound-statement"
#define SYMBOL_DECLARATION_LIST "declaration-list"
#define SYMBOL_STATEMENT_LIST "statement-list"
#define SYMBOL_EXPRESSION_STATEMENT "expression-statement"
#define SYMBOL_SELECTION_STATEMENT "selection-statement"
#define SYMBOL_ITERATION_STATEMENT "iteration-statement"
#define SYMBOL_JUMP_STATEMENT "jump-statement"

/* 6.7 External definitions */
#define SYMBOL_TRANSLATION_UNIT "translation-unit"
#define SYMBOL_EXTERNAL_DECLARATION "external-declaration"
#define SYMBOL_FUNCTION_DEFINITION "function-definition"

/* Other symbols */
#define SYMBOL_THEN_STATEMENT "then-statement"
#define SYMBOL_ELSE_STATEMENT "else-statement"
#define SYMBOL_INIT_EXPRESSION "init-expression"
#define SYMBOL_COND_EXPRESSION "cond-expression"
#define SYMBOL_ITER_EXPRESSION "iter-expression"

#define SYMBOL_ALLOC_BLOCK "alloc-block"
#define SYMBOL_ENTRY_BLOCK "entry-block"
#define SYMBOL_EXPR_TAG "expr-tag"
#define SYMBOL_HAS_DEFAULT "has-default"
#define SYMBOL_IMMEDIATE "immediate"
#define SYMBOL_MODULE_FUNCTIONS "module-functions"
#define SYMBOL_MODULE_TABLE "module-table"
#define SYMBOL_MUST_RETURN "must-return"
#define SYMBOL_RETURN_EXTRA "return-extra"
#define SYMBOL_TABLE_GLOBAL "table-global"
#define SYMBOL_TABLE_NEXT "table-next"
#define SYMBOL_TABLE_SYMBOLS "table-symbols"

#endif /* INCLUDE_GUARD_E0353946_9774_492C_A775_4B26998B01E8 */
