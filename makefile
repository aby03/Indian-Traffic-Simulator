IDIR = ./include
CC = g++
CFLAGS = -I$(IDIR) -std=c++11 -g

ODIR = ./build
EDIR = ./bin
SDIR = ./src

# _DEPS = imgOp.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = simulator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(EDIR)/simulator $(EDIR)/readconfig

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/simulator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/readconfig.o: $(SDIR)/readconfig.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/readconfig: $(ODIR)/readconfig.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*