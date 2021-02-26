#include "output.h"

// output bytes
bool
writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

void writebytessys(int nbytes, int size, unsigned long long (*rand64) (void)) {
  // initialize variables and allocate memory for the buffer
  char* buffer = (char *) malloc(size < nbytes? size : nbytes); 
  int iteration = nbytes/size + (nbytes%size < 1? nbytes%size : 1);

  // malloc failure
  if (!buffer){
    fprintf(stderr,
                "Error: Filed to allocate memory for characters\n");
    exit(EXIT_FAILURE);
  }
  
  //printf("%d", iteration);
  for(int i = 0; i < iteration; i++){
    // bytes written each time
    int wbytes;
    // bytes left less than buffersize
    if(nbytes - i*size < size)
      wbytes = nbytes - i*size; 
    else
      wbytes = size; 

    // temporarily store size
    int sTemp = size;
    // generate random number
    unsigned long long x = rand64();
    // move number into buffer
    for(int j = 0, s = 0; j < sTemp; j++, s++){
      // for every 8 bytes written -> generate a new number
      if(j%8 == 0 && j){
        // generate random number
        x = rand64();
        s = 0;
      }
      buffer[j] = x >> (s*8) & 0xff;
    }

    // write to stdout
    if(write(1, buffer, wbytes)<0){
	fprintf(stderr, "Error: write failed\n");
	exit(EXIT_FAILURE);
    }
  }
  
  // free memory at the end
  free(buffer);
}
