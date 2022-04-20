LDFLAGS = -L../simple-jpeg/ -lsimplejpeg -L /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib/
SRC 			:= $(wildcard *.c)
FLAGS = mpicc

EXE = parallel_main.x

all:  $(EXE) simple-jpeg execute

$(EXE): $(SRC) 
	$(FLAGS) -lm  $(SRC) -o $@ $(LDFLAGS) 

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

execute:
	mpirun -np 4 ./parallel_main.x 0.2 20 "mona_lisa_noisy.jpeg" "mona_lisa_clean.jpeg"

clean:
	$(MAKE) execute-clean
	$(MAKE) $(EXE)-clean
	$(MAKE) $(SRC)-clean
	$(MAKE) -C ../simple-jpeg clean