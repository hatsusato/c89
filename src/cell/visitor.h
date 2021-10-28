#ifndef INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F
#define INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F

#include "util/type.h"

struct cell;
struct cell_visitor;
struct dict;
typedef bool_t (*cell_visitor_t)(const struct cell *, void *);
struct cell_visitor_wrapper {
  cell_visitor_t func;
};

void cell_visitor(const struct cell *, const struct dict *, void *);
bool_t cell_visitor_noop(const struct cell *, void *);

struct cell_visitor *cell_visitor_new(void *);
void cell_visitor_delete(struct cell_visitor *);
void cell_visitor_insert(struct cell_visitor *, const char *, cell_visitor_t);

#endif /* INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F */
