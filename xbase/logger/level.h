/* $Id: priority.h,v 1.5 2006/10/01 18:28:55 rbyrne Exp $
 *
 * priority.h
 * 
 * Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef X__LOGGER_LEVEL_H
#define X__LOGGER_LEVEL_H

#include "xdefs/xdefs.h"
__X_BEGIN_DECLS

#define X_LEVEL_FATAL        (1)
#define X_LEVEL_ALERT        (1<<1)
#define X_LEVEL_CRIT         (1<<2)
#define X_LEVEL_ERROR        (1<<3)
#define X_LEVEL_WARN         (1<<4)
#define X_LEVEL_NOTICE       (1<<5)
#define X_LEVEL_INFO         (1<<6)
#define X_LEVEL_DEBUG        (1<<7)
#define X_LEVEL_TRACE        (1<<8)

typedef int32                log_level_t;
#define LOG_LEVEL_IS(TEST_LEVEL, TARGET_LEVEL) (TEST_LEVEL==TARGET_LEVEL)
#define LOG_LEVEL_HAS(TEST_LEVEL, TARGET_LEVEL) ((TEST_LEVEL&TARGET_LEVEL)==TARGET_LEVEL)

X_LOCAL const char* x_level_to_string(int32 a_level);
X_LOCAL int32 x_level_to_int(const char* a_level_name);

__X_BEGIN_DECLS
#endif //X__LOGGER_LEVEL_H
