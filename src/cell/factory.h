#ifndef INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1
#define INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1

struct cell_factory;
struct pool_any;

struct cell_factory *cell_factory_new(struct pool_any *);
void cell_factory_delete(struct cell_factory *);

#endif /* INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1 */
