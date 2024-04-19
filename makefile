CC=cl65
CFLAGS=-t c64 -O -I .\deps
DEPS = graphics.h iolib.h letters.h
OBJ = main.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin\robco: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)