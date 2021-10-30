#ifndef INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6
#define INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6

#include "yyscan_t.h"

struct json_factory;
struct set;

struct scanner {
  struct set *typedefs;
  struct set *symbols;
  struct json_factory *jfactory;
  YYSCAN_TYPE top;
};

#endif /* INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6 */
