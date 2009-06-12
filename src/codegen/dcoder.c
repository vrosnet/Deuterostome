#line 2 "./dcoder.c.in"

#include "dm-config.h"
#ifdef DM_HAVE_CONFIG_H
#ifndef DM_INCLUDED_CONFIG_H
#define DM_INCLUDED_CONFIG_H
#include "config.h"
#endif
#endif

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "dm-errs.h.built"

#define DM_IGNORE_RETURN(a) if (a);

__attribute__ ((unused, format (printf, 3, 4)))
static void error_dcoder(int __status, 
			int __errnum, 
			const char* __format, ...)
{
  char* str;
  int s;

  va_list ap;
  va_start(ap, __format);
  if (vasprintf(&str, __format, ap) != -1) {
    DM_IGNORE_RETURN(write(STDERR_FILENO, str, strlen(str)));
    free(str);
  }
  if (__errnum) s = asprintf(&str, ": %s\n", strerror(__errnum));
  else s = asprintf(&str, "\n");
  if (s != -1) {
    DM_IGNORE_RETURN(write(STDERR_FILENO, str, strlen(str)));
    free(str);
  }
  if (__status) exit(__status);
}


struct emap {
  char* str;
  long val;
};

#include "dcoder.h"

int main(int argc, char* argv[]) {
  FILE* fd;
  struct emap* cemap;
  int i = 0;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <path>\n", argv[0]);
    return 1;
  }

  if (! (fd = fopen(argv[1], "w")))
    error_dcoder(1, errno, "Unable to open for writing: %s", argv[1]);

  if (fprintf(fd, "(Using errors.d  $" "Id$ V@" "PACKAGE_VERSION@ @"
	      "SVNVERSION@\\n) toconsole\n") < 0)
    error_dcoder(1, errno, "Unable to write line# %i", i);
  i++;

  if (fprintf(fd, "/ERRORS module 1000 dict dup begin\n") < 0)
    error_dcoder(1, errno, "Unable to write line# %i", i);
  i++;

  for (cemap = emap; cemap->str; cemap++, i++)
    if (fprintf(fd, "  /%-29s %8lldx def\n", 
		cemap->str, (long long) cemap->val) < 0)
      error_dcoder(1, errno, "Unable to write line# %i", i);

  if (fprintf(fd, "end _module\n") < 0)
    error_dcoder(1, errno, "Unable to write line# %i", i);

  return 0;
}
