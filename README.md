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
	./main.x "100nodes_graphs.txt" 0.85 1e-8 8
```  
To run the makefile, simply write "make all" in the terminal. The 4 arguments to the makefile are described in the line above the execute command, and are 
used as the followinf
- Filename: name of the filed used in calculations, needs to be string
- d: damping constant (default 0.85)
- Epsilon: convergence threshold value
- n: the number of the top webpages printed to terminal after calculation
<br>
The filename must be set to whatever the name of the file is added to the folder. The three textfiles included in this folder is: test.txt, 100nodes_graphs.txt and web-Stanford_p.txt. The textfiles are written from smallest to largest. Note that the web-Stanford_p, is taken from the project-description, but has benn altered to the use of a python code, as the data was most likely initialy written for fortran. <br>

In addition there are two details in the compile-line. I have added a flag called "-fsanitize=address", which is used to controll memory leaks.
And I have added gcc-11. Not all computers need the gcc-11 specified, but my computer did.<br>

An example is to run with the following execute-command: "./main.x "web-Stanford_p.txt" 0.85 1e-8 8". The printed result will be the following:
```
- - - - - - - - - - - - - - - -
Number of nodes: 281903 --- Number of edges: 2312497
- - - - - - - - - - - - - - - -
Hyperlink matrix built: Format -> CRS.
- - - - - - - - - - - - - - - - - -
Nr of dangling webpages: 172
- - - - - - - - - - - - - - - - - -
Calculating scores....
- - - - - - - - - - - - - - - - - -
Threshold (1.00e-08) reached after  235 iterations. 
- - - - - - - - - - - - - - - - - -
----------------------------------
--------* Highest scores *--------
----------------------------------
 1. -- score: 0.011 -- index: 89072
 2. -- score: 0.009 -- index: 226410
 3. -- score: 0.008 -- index: 241453
 4. -- score: 0.003 -- index: 262859
 5. -- score: 0.003 -- index: 134831
 6. -- score: 0.003 -- index: 234703
 7. -- score: 0.002 -- index: 136820
 8. -- score: 0.002 -- index: 68888
```
 
