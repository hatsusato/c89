#ifndef INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696
#define INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696

struct pool_any;
struct set_symbol;

struct cell {
  const void *car;
  const struct cell *cdr;
};

struct cell_factory {
  struct pool_any *pool;
  struct set_symbol *set;
};

#endif /* INCLUDE_GUARD_973F8446_963B_4832_B66D_D002FE861696 */
