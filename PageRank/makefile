all: compile execute

compile:
	gcc-11 -Wall -fopenmp -o main.x main.c

execute:
	#filename -- d -- epsilon -- n
	./main.x "100nodes_graphs.txt" 1. 1e-6 8
	
