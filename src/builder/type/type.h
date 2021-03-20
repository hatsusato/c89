#ifndef INCLUDE_GUARD_6731EFF8_DFC1_4FE2_8581_A5D2793922D5
#define INCLUDE_GUARD_6731EFF8_DFC1_4FE2_8581_A5D2793922D5

#include "utility/types.h"

Type *builder_type_void(Builder *);
Type *builder_type_bool(Builder *);
Type *builder_type_int(Builder *);
Type *builder_type_pointer(Builder *, Type *);
Type *builder_type_label(Builder *);

#endif /* INCLUDE_GUARD_6731EFF8_DFC1_4FE2_8581_A5D2793922D5 */
