#include <stdlib.h>
#include <unistd.h>

#include "get_line.h"

char*	_get_socket(_fd fd) {
  char* buff;
  int	itt;
  char	c;

  itt = 0;
  buff = NULL;
  while (read(fd, &c, 1)) {
    buff = realloc(buff, itt + 1);
    if (c == '\n')
      break;
    buff[itt] = c;
    itt += 1;
  }
  return (buff);
}
