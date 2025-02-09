HDIR = headers
SDIR = src
OUTDIR = $(SDIR)/out

CC = gcc
CFLAGS = -std=c99 -Wall -I $(HDIR)
LIBS = -lncurses

EXENAME = tetr

SRC = $(wildcard $(SDIR)/*.c)
OBJ = $(patsubst $(SDIR)/%.c, $(OUTDIR)/%.o, $(SRC))

all: $(OUTDIR) $(OUTDIR)/$(EXENAME)

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OUTDIR)/%.o: $(SDIR)/%.c $(wildcard $(HDIR)/*.h) | $(OUTDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/$(EXENAME): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

.PHONY: run
run:
	$(OUTDIR)/$(EXENAME)
