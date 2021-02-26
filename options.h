#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "rand64-hw.h"
#include "rand64-sw.h"
#include "rand64-mrand.h"

// command-line options:
struct options {
 // function pointers 
 void (*initialize) (void);
 unsigned long long (*rand64) (void);
 void (*finalize) (void);
 // number of bytes
 long long nbytes;
 // input
 char* input;
 // output
 char* output; 
};

// process nbytes with result returned
void argProcess(int, char**, struct options*);
void parseArgs(int, char**, struct options*);
void inputProcess(struct options*);
void hwInput(struct options*);
void swInput(struct options*);
void mrandInput(struct options*);
