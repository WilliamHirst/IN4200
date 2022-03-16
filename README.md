# IN4200 Project 1 - Computing PageRank

In this folder you will find 8 files: 4 C-files containing the 3 functions used for calculation and the main-file, a makefile and three textfiles containing 
data. Each of the 3 files conatining the functions are named after the functions: read_graph_from_file.c, PageRank_iterations and top_n_webpages. The main
file includes all three of this functions in the beginning and is compiled by the makefile.
The makefile is written as such <br>

```
all: compile execute

compile:
	gcc-11 -Wall -fsanitize=address -fopenmp -o main.x main.c

execute:
	#filename -- d -- epsilon -- n
	./main.x "web-Stanford_p.txt" 0.85 1e-8 10
```  
To run the makefile, simply write "make all" in the terminal. The 4 arguments to the makefile are described in the line above the execute command, and are 
used as the followinf
- Filename: name of the filed used in calculations
- d: damping constant (default 0.85)
- Epsilon: convergence threshold value
- n: the number of the top webpages printed to terminal after calculation
<br>
The filename must be set to whatever the name of the file is added to the folder. The three textfiles included in this folder is: test.txt, 100nodes_graphs.txt and web-Stanford_p.txt. The textfiles are written from smallest to largest. Note that the web-Stanford_p, is taken from the project-description, but has benn altered to the use of a python code, as the data was most likely initialy written for fortran. <br>

In addition I have added a flag called "-fsanitize=address", which is used to controll memory leaks. 
 
