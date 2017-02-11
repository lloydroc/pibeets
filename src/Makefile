#LIBS  = -lkernel32 -luser32 -lgdi32 -lopengl32
CFLAGS = -Wall

SRC=$(wildcard *.c)
pibeets: $(SRC)
	gcc -o $@ $^ $(CFLAGS)
