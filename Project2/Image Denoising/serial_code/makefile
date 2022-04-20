LDFLAGS = -L../simple-jpeg/ -lsimplejpeg 
SRC 			:= $(wildcard *.c)
OBJS = serial_main.o ../Funcs/functions.o
FLAGS = gcc -Wall -fsanitize=address 
PROJ = serial_main

all: simple-jpeg $(PROJ) $(OBJS) execute clean

serial_main: $(OBJS) 
	$(FLAGS) $(OBJS) -o $@.x $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

execute:
	./serial_main.x 0.2 100 "mona_lisa_noisy.jpeg" "mona_lisa_clean.jpeg"

objs-clean:
	$(RM) *.o
	$(RM) ../Funcs/*.o
exec-clean:
	$(RM) *.x

clean:
	$(MAKE) objs-clean
	$(MAKE) exec-clean
	$(MAKE) -C ../simple-jpeg clean