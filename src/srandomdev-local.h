/*

Copyright 2011 Alexander Peyser & Wolfgang Nonner

This file is part of Deuterostome.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef SRANDOM_H
#define SRANDOM_H

#include "dm.h"

#include <stdlib.h>
#include <unistd.h>

#if !DM_HAVE_SRANDOMDEV

#include <errno.h>
#include <time.h>
#include <fcntl.h>

DM_INLINE_STATIC void srandomdev(void) 
{
  int unsigned long seed;
  int off = 0;
  int r;
  
  int fd = open("/dev/random", O_RDONLY, 0);
  if (fd == -1) {
    srandom(time(NULL));
    return;
  }

  while (off < sizeof(seed)) {
      if ((r = read(fd, (char*) &seed + off, sizeof(seed))) == -1) {
        if (errno != EINTR) {
          seed = time(NULL);
          break;
        }
        r = 0;
      }
      off += r;
    }
				
  while (close(fd) && errno == EINTR);
  srandom(seed);
}


#endif //!DM_HAVE_SRANDOMDEV

#endif //SRANDOM_H
