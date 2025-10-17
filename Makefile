# header files
IDIR = include

# compile command and flags
CC = gcc
CFLAGS = -I$(IDIR)

LIBS = -lm

# object files directory
ODIR = src

# build paths
_DEPS = sicario.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sicario.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

# default goal
all: sicario

# build rules
$(ODIR)/%.o: $(ODIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

sicario: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS)

clean:
	rm -f $(ODIR)/*.o sicario *~ core $(IDIR)/*~
