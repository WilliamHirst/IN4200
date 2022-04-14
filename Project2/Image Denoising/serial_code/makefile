LDFLAGS = -L../simple-jpeg/ -lsimplejpeg
SRC 			:= $(wildcard *.c)
FLAGS = gcc-11 -Wall -fsanitize=address
EXE = serial_main.x

all:  $(EXE) simple-jpeg execute

$(EXE): $(SRC) 
	$(FLAGS) $(SRC) -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

execute:
	./serial_main.x 0.2 10 "mona_lisa_noisy.jpeg" "mona_lisa_clean.jpeg"

clean:
	$(MAKE) execute-clean
	$(MAKE) compile-clean
	$(MAKE) -C ../simple-jpeg clean