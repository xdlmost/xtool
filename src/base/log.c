#include "base/log.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "base/x_memory.h"

#define DEFAULT_LINE_MAX 1024

void 
__x_log_(char type, cstr func_name, cstr file_name, u32_t line, cstr format, ...)
{
  va_list	args;
  int written;
  char buffer[DEFAULT_LINE_MAX];
  char *p;
  i32_t capacity = DEFAULT_LINE_MAX ;
  u32_t rest_size = capacity-2;

  p = buffer;
  written = snprintf(p, rest_size, "[%c|%s|%s:%d]", type, func_name, file_name, line);

  p += written;
  rest_size -= written;

  if(rest_size > 0) {
    va_start(args, format);
    written = vsnprintf(p, rest_size, format, args);
    p += written;
    rest_size -= written;
    va_end(args);
  }

  *(p++) = '\n';
  *p = 0;

  fputs(buffer, stdout);
}