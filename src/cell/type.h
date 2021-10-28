#ifndef INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696
#define INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696

struct dict;
struct pool;
struct set;

struct cell {
  const void *car;
  const struct cell *cdr;
};

struct cell_factory {
  struct pool *pool;
  struct set *set;
};

struct cell_visitor {
  struct pool *wrappers;
  struct dict *visitors;
  void *extra;
};

#endif /* INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696 */
