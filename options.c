#include "options.h"

// process nbytes with result returned
bool argProcess(int argc, char** argv, struct options *op){
  /* Check arguments.  */
  bool valid = false;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      op->nbytes = strtoll (argv[1], &endptr, 10); 
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= op->nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
    }
  
  // return whether arguments are valid
  return valid; 
}



