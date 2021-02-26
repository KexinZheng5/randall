#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// output bytes
bool writebytes(unsigned long long, int);
void writebytessys(int, int, unsigned long long (*rand64) (void));
