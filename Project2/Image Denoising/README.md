# Image Denoising
In this folder you will find 3 folders; serial_code, parallel_code and Funcs. Note, to run the code, make sure the folder "simple-jpeg"<br>
is placed inside this folder next to the other three. <br>

Serial code contains a makefile, the main file which runs the code and an image ("mona_lisa_noisy").
The make file has 6 functions. Two functions compile and make all necassary functions, both in simple-jpeg, in Funcs and in <br>
serial_main. Three functions are used to clean all ".o"-  and ".x"-files. The last function executes the serial_main function <br>
and will execute the folllowing line: <br>

```
  ./serial_main.x 0.2 10 "mona_lisa_noisy.jpg" "mona_lisa_clean.jpg"
```
The arguments in the lines are defined as the following:
  - kappa: a small scalar constant,
  - iters: number of iterations,
  - input filename: name of noisy file, 
  - output filename: prefered name of unoised file.
 <br>
To run the makefile, simply write "make all" in terminal. Running the makefile should print the following statements if <br>
succsessfully;

```
JPEG imported.
Pixels -> [W: 4289, H: 2835]
Calculating iterations...
10 iterations completed.
Denoised image exported.
Finished.
```
Inside parallel_code you will find the same as for serial, but with the main; parallel_code. The makefile for parallel is the same as for serial, but uses mpicc instead of gcc.  To run the parallel code, simply write "make all". <br>

In the folder Funs there are two c-files; functions.c and functions_p.c. "functions.c" has all functions need for the calculations in serial and most of parallel. In "functions_p.c" there is only one functions: iso_diffusion_denoising_parallel.
<br>

