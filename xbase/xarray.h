#ifndef X_ARRAY_H
#define X_ARRAY_H

#include "xdefs/xdefs.h"
__X_BEGIN_DECLS

typedef struct xarray xarray;

X_LOCAL xret create_array(uint32 capacity, uint32 value_size, xarray **newarray);
X_LOCAL cstr get_type(xarray *self);

__X_END_DECLS

#endif
