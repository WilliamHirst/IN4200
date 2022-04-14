CC = gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
EX = serial_main.exe

all: simple-jpeg $(EX)


$(EXEC): 
	$(CC) $(CFLAGS) -lm -o $@ $(LDFLAGS)
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c

simple-jpeg:
	$(MAKE) -C ../simple-jpeg


exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean
