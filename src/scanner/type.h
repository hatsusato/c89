#ifndef INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6
#define INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6

struct cell;
struct pool;

struct scanner {
  struct pool *pool;
  const struct cell *ast;
};

#endif /* INCLUDE_GUARD_0EF6CD70_0EFD_47E7_8494_CAD9D7637AB6 */
