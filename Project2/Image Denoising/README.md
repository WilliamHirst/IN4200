# Image Denoising
In this folder you will find 3 folders; serial_code, parallel_code and Funcs. Note, to run the code the folder "simple-jpeg"<br>
must be placed inside this folder next to the other three. <br>

Serial code contains a makefile, the main file which runs the code and an image ("mona_lisa_noisy").
The make file has 6 functions. Two functions compile and make all necassary functions, both in simple-jpeg, in Funcs and in <br>
serial_main. Three functions are used to clean all ".o"-  and ".x"-files. The last function executes the serial_main function <br>
will execute the folllowing line <br>

```
  ./serial_main.x 0.2 10 "mona_lisa_noisy.jpg" "mona_lisa_clean.jpg"
```
, where the arguments define kappa, number of iterations, name of noisy file and prefered name of unoised file respectivly.<br>
To run the makefile, simply write "make all" in terminal. Running the makefile should print the following statements if <br>
succsessfull. 

