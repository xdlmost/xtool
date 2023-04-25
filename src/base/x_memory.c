#include "base/x_memory.h"
#include <stdlib.h>
#include <string.h>

inline pt_t 
x_malloc(u32_t ele_size)
{
  return malloc(ele_size);
}

inline pt_t 
x_calloc(u32_t ele_size, u32_t ele_count)
{
  return calloc(ele_size, ele_count);
}

inline pt_t 
x_realloc(pt_t mem, u32_t new_size)
{
  return realloc(mem, new_size);
}

inline void
x_free(pt_t mem)
{
  free(mem);
}

inline pt_t 
x_memcpy(pt_t dest, cpt_t src, u32_t count)
{
  return memcpy(dest, src, count);
}

inline pt_t 
x_memmove(pt_t dest, cpt_t src, u32_t count)
{
  return memmove(dest, src, count);
}

inline pt_t 
x_memset(pt_t dest, int val, u32_t count)
{
  return memset(dest, val, count);
}

inline pt_t 
x_memzero(pt_t dest, u32_t count)
{
  return memset(dest, 0, count);
}

inline int 
x_memcmp(cpt_t cmp1, cpt_t cmp2, u32_t count)
{
  return memcmp(cmp1, cmp2, count);
}

