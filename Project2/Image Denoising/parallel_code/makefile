LDFLAGS = -L../simple-jpeg/ -lsimplejpeg 
PROJ = parallel_main
CC = mpicc
OBJS = parallel_main.o ../Funcs/functions.o ../Funcs/functions_p.o
FLAGS = -O2 -Wall -fsanitize=address 


all: simple-jpeg $(PROJ) $(OBJS) execute clean

parallel_main: $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $@.x $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

execute:
	mpirun -np 4 ./parallel_main.x 0.2 100 "mona_lisa_noisy.jpg" "mona_lisa_clean.jpg"

objs-clean:
	$(RM) *.o
	$(RM) ../Funcs/*.o

exec-clean:
	$(RM) *.x

clean:
	$(MAKE) objs-clean
	$(MAKE) exec-clean
	#@$(MAKE) -C ../simple-jpeg clean
	