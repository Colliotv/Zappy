#include <stdlib.h>
#include <unistd.h>

#include "get_line.h"

char*	_get_socket(_fd fd) {
  char* buff;
  int	itt;
  char	c;

  itt = 0;
  buff = NULL;
  c = 0;
  while (c != '\n' && read(fd, &c, 1) > 0)
    {
      buff = realloc(buff, itt + 1);
      buff[itt] = c;
      itt += 1;
      if (c == '\n')
	buff = realloc(buff, itt + 1);
      if (c == '\n')
	buff[itt] = 0;
    }
  return (buff);
}
