/****************************************************
 * Author: xdlmost(xdeliver@163.com)
 * Description: 
 * Note: 
 ****************************************************/
#ifndef __X_ATOMIC_H
#define __X_ATOMIC_H 1
#include "predefine.h"
__X_BEGIN_DECLS

/**
 * Atomically read a int32 value from memory
 * @param mem The memory
 * @return the value at mem
 */
X_API(u32_t) x_atomic_read32(const volatile u32_t *mem);

/**
 * Atomically set a int32 value to memory
 * @param mem The memory
 * @param val The value
 */
X_API(void) x_atomic_set32(volatile u32_t *mem, u32_t val);

/**
 * Atomically add a value to memory
 * @param mem The memory
 * @param val The value
 * @return the old value at mem
 */
X_API(u32_t) x_atomic_add32(volatile u32_t *mem, u32_t val);

/**
 * Atomically substract a value to memory
 * @param mem The memory
 * @param val The value
 */
X_API(void) x_atomic_subtract32(volatile u32_t *mem, u32_t val);

/**
 * Atomically increment mem by 1 
 * @parma mem The memory
 * @return The old value of mem
 */
X_API(u32_t) x_atomic_increment32(volatile u32_t *mem);

/**
 * Atomically decrement mem by 1
 * @param mem The memory
 * @return Zero if the value after decrement is 0. Otherwise, non-zero.
 */
X_API(u32_t) x_atomic_decrement32(volatile u32_t *mem);


__X_END_DECLS
#endif //__X_ATOMIC_H