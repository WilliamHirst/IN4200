LDFLAGS = -L../simple-jpeg/ -lsimplejpeg
SRC 			:= $(wildcard *.c)
FLAGS = mpicc  -Wall  -fsanitize=address 


EXE = parallel_main.x

all:  $(EXE) simple-jpeg execute

$(EXE): $(SRC) 
	$(FLAGS) $(SRC) -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

execute:
	./parallel_main.x 0.2 20 "mona_lisa_noisy.jpeg" "mona_lisa_clean.jpeg"

clean:
	$(MAKE) execute-clean
	$(MAKE) compile-clean
	$(MAKE) -C ../simple-jpeg clean