#include "base/x_memory.h"
#include<stdlib.h>

pt 
x_malloc(u32_t ele_size)
{
  return malloc(ele_size);
}

pt 
x_calloc(u32_t ele_size, u32_t ele_count)
{
  return calloc(ele_size, ele_count);
}

pt 
x_realloc(pt mem, u32_t new_size)
{
  return realloc(mem, new_size);
}

void
x_free(pt mem)
{
  free(mem);
}
