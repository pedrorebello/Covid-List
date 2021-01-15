PATHI = ./include
PATHO = obj
PATHS = src
PATHT = test

CC = gcc
CFLAGS = -I$(PATHI)

LIBS = -lm

_DEPS = list.h logic.h main.h persistence.h
DEPS = $(patsubst %,$(PATHI)/%,$(_DEPS))

_OBJ = list.o logic.o main.o persistence.o
OBJ = $(patsubst %,$(PATHO)/%,$(_OBJ))

$(PATHO)/%.o: $(PATHS)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

covidlist: $(OBJ)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	del $(PATHO)\*.o
