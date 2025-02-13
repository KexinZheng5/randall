#include "rand64-mrand.h"

static struct drand48_data buffer;

// initialize
void mrand48_init(void){
    // initialize data buffer
    srand48_r(time(0), &buffer);
}

// generate character
unsigned long long mrand48_rand64(void){
  // most and least significant bits
  long int most;
  long int least;
  mrand48_r(&buffer, &most);
  mrand48_r(&buffer, &least);
  least = (unsigned long long int)least & 0xffffffff;
  // form 64 bit integer
  return ((unsigned long long int)most << 32) | least; 
}

// finalize
void mrand48_rand64_fini(void){
}
