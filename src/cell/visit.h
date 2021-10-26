#ifndef INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F
#define INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F

struct cell;
struct dict;
typedef void (*cell_visitor_t)(const struct cell *, void *);
struct cell_visitor_wrapper {
  cell_visitor_t func;
};

void cell_visitor(const struct cell *, const struct dict *, void *);

#endif /* INCLUDE_GUARD_1EE525F3_DB92_4F96_8208_3D730F3BA78F */
