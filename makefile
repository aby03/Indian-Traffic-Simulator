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

all: $(EDIR)/readconfig $(EDIR)/test $(EDIR)/gl_sim 

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/readconfig.o: $(SDIR)/readconfig.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/readconfig: $(ODIR)/readconfig.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/test.o: $(SDIR)/test.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/test: $(ODIR)/test.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/gl_sim.o: $(SDIR)/gl_sim.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(EDIR)/gl_sim: $(ODIR)/gl_sim.o
	$(CC) -o $@ $^ $(CFLAGS) -lGL -lGLU -lglut

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EDIR)/*