#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// command-line options:
struct options {
 // function pointers 
 void (*initialize) (void);
 unsigned long long (*rand64) (void);
 void (*finalize) (void);
 // number of bytes
 long long nbytes;
 // output
 char* output; 
};

// process nbytes with result returned
bool argProcess(int, char**, struct options*);
