/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "options.h"
#include "output.h"
#include "rand64-mrand.h"
#include "rand64-hw.h"
#include "rand64-sw.h"

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  // process argument
  struct options op; 
  argProcess(argc, argv, &op);

  // no work -> exit program
  if (op.nbytes == 0){
    printf("not working 0");
    return 0;
  }
  
  
  // initialize
  op.initialize ();
  int wordsize = sizeof op.rand64 ();
  int output_errno = 0;

  // stdio output
  if (!op.output || !strcmp(op.output, "stdio"))
  {
    do
      {
	unsigned long long x = op.rand64 ();
	int outbytes = op.nbytes < wordsize ? op.nbytes : wordsize;
	if (!writebytes (x, outbytes))
        {
          output_errno = errno;
          break;
        }
	op.nbytes -= outbytes;
      }
    while (0 < op.nbytes);

    if (fclose (stdout) != 0)
      output_errno = errno;

    if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }
  }
  // write system call
  else{
    // validate output
     char *endptr;
     errno = 0;
     int n = strtol (op.output, &endptr, 10);
     //printf("%d\n", n);
     //printf("%d\n", errno);
     //printf("%d\n", *endptr);
     if (errno || (*endptr)){
       fprintf(stderr,
	       "Error: invalid output (can't be zero)\n");
       exit(EXIT_FAILURE);
     }
     writebytessys(op.nbytes,n,op.rand64);
  }

  op.finalize ();
  return !!output_errno;
}
