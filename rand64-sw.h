#pragma once

#include <stdio.h>
#include <stdlib.h>

void setInput (char*);
void software_rand64_init (void);
unsigned long long software_rand64 (void);
void software_rand64_fini (void);
