#ifndef __LERROR_H__
# define __LERROR_H__

#include <stdio.h>

void	lerror(const char*, ... );

# define MEMORY_ERROR_UNSPECIFIED "memory allocation fail\n"
# define MEMORY_ERROR(size) "memory allocation fail on %u bytes\n", size

# define NAMES_UNITIALIZED "ERROR: teams name non-initialized, process will quit\n"

#endif
