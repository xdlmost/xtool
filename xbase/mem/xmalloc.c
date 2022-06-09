#include "xbase/mem/xmalloc.h"
#include <stdlib.h>
void *
xmalloc(uint32 n) {
    return malloc(n);
}

void *
xrealloc(void *p, uint32 n) {
    return realloc(p, n);
}

void *
xcalloc(uint32 n, uint32 s) {
    return calloc(n, s);
}

void xfree(void *p){
    free(p);
}