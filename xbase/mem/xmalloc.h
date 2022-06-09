#ifndef X_MALLCO_H
#define X_MALLCO_H
#include "xdefs/xdefs.h"
__X_BEGIN_DECLS

X_LOCAL void *xmalloc(uint32 n);
X_LOCAL void *xrealloc(void *p, uint32 n);
X_LOCAL void *xcalloc(uint32 n, uint32 s);
X_LOCAL void  xfree(void *p);

__X_BEGIN_DECLS
#endif