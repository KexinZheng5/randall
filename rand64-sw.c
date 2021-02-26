#include "rand64-sw.h"

/* Input stream containing random bytes.  */
static FILE *urandstream;
static char * fName;

// set input file name
void
setInput(char* fileName){
  fName = fileName;
}
  
/* Initialize the software rand64 implementation.  */
void
software_rand64_init (void)
{
  urandstream = fopen (fName, "r");
  if (! urandstream){
    fprintf(stderr, "Error: failed to open input file: %s\n", fName);
    exit(2);
  }
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}
