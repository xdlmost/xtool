#include "base/x_memory.h"
#include <stdlib.h>
#include <string.h>

inline pt 
x_malloc(u32_t ele_size)
{
  return malloc(ele_size);
}

inline pt 
x_calloc(u32_t ele_size, u32_t ele_count)
{
  return calloc(ele_size, ele_count);
}

inline pt 
x_realloc(pt mem, u32_t new_size)
{
  return realloc(mem, new_size);
}

inline void
x_free(pt mem)
{
  free(mem);
}

inline pt 
x_memcpy(pt dest, cpt src, u32_t count)
{
  return memcpy(dest, src, count);
}

inline pt 
x_memmove(pt dest, cpt src, u32_t count)
{
  return memmove(dest, src, count);
}

inline pt 
x_memset(pt dest, int val, u32_t count)
{
  return memset(dest, val, count);
}

inline pt 
x_memzero(pt dest, u32_t count)
{
  return memset(dest, 0, count);
}

inline int 
x_memcmp(cpt cmp1, cpt cmp2, u32_t count)
{
  return memcmp(cmp1, cmp2, count);
}

