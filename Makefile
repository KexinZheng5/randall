# Make x86-64 random byte generators.

# Copyright 2015, 2020 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = -cvzf
TAREXT = tgz

default: randall

randall: randall.o options.o output.o rand64-hw.o rand64-sw.o rand64-mrand.o
	$(CC) $(CFLAGS) randall.o options.o output.o rand64-hw.o rand64-sw.o\
	 rand64-mrand.o -o randall

objectFiles: randall.c options.c output.c rand64-hw.c rand64-sw.c rand64-mrand.c
	make randall.o
	make options.o
	make output.o
	make rand64-hw.o
	make rand64-sw.o
	make rand64-mrand.o

randall.o: randall.c
	$(CC) $(CFLAGS) -c randall.c -o randall.o

options.o: options.c
	 $(CC) $(CFLAGS) -c options.c -o options.o

output.o: output.c
	$(CC) $(CFLAGS) -c output.c -o output.o

rand64-hw.o: rand64-hw.o
	$(CC) $(CFLAGS) -c rand64-hw.c -o rand64-hw.o

rand64-sw.o: rand64-sw.c
	$(CC) $(CFLAGS) -c rand64-sw.c -o rand64-sw.o

rand64-mrand.o: rand64-mrand.c
	$(CC) $(CFLAGS) -c rand64-mrand.c -o rand64-mrand.o

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) $@ $(assignment-files)

submission: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt options.c output.c rand64-hw.c rand64-sw.c rand64-mrand.c\
  options.h output.h rand64-hw.h rand64-sw.h rand64-mrand.h\
  randall test

randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) $@ $(submission-files)

.PHONY: default clean assignment submission

clean:
	rm -f *.o *.$(TAREXT) randall

clean.o:
	rm -f *.o

clean~: 
	rm -f *~

check: randall test
	./test
