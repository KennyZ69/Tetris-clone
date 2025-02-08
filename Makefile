
HDIR = headers
SDIR = src

OUTDIR = $(SDIR)/out

LIBS = -lncurses
CFLAGS = -std=c99 -I $(HDIR) -Wall

EXENAME = tetr

all: # finish this call

.PHONY: clean

clean:
	rm $(OUTDIR)/*.o $(EXENAME)
