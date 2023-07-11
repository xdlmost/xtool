/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_COMPARE_FUNS_H
#define __X_COMPARE_FUNS_H 1
#include "predefine.h"
__X_BEGIN_DECLS

/**
 * Compare two values. If not set.
 * @param value1 The first value
 * @param value2 The second value
 * @return <0 if value1 is less than value2
 *         =0 if value1 is equal to value2
 *         >0 if value1 is greater than value2
 */
typedef i32_t (*x_compare_func)(cpt_t value1, cpt_t value2);

X_API(i32_t) x_compare_func_i32_ptr(cpt_t value1, cpt_t value2);

X_API(i32_t) x_compare_func_i32(i32_t value1, i32_t value2);


__X_END_DECLS
#endif //__X_COMPARE_FUNS_H