#include "base/x_compare_funs.h"

inline i32_t 
x_compare_func_i32_ptr(cpt_t value1, cpt_t value2, pt_t arg)
{
  i32_t valuei32_t1 = *(i32_t *)value1;
  i32_t valuei32_t2 = *(i32_t *)value2;
  return x_compare_func_i32(valuei32_t1, valuei32_t2);
}

inline i32_t 
x_compare_func_i32(i32_t value1, i32_t value2)
{
  if (value1 > value2) {
    return 1;
  } else if (value1 < value2) {
    return -1;
  }

  return 0;
}