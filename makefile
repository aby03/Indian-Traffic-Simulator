IDIR = ./include
CC = g++
CFLAGS = -I$(IDIR) -std=c++11 -g

ODIR = ./build
EDIR = ./bin
SDIR = ./src

# _DEPS = imgOp.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = readconfig.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(EDIR)/readconfig $(EDIR)/test 

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/readconfig: $(ODIR)/readconfig.o
	$(CC) -o $@ $^ $(CFLAGS)

$(EDIR)/test: $(ODIR)/test.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*