all: compile execute

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c

execute:
	#filename -- d -- epsilon -- n
	./main.x "test.txt" 0.85 1e-8 8
	
