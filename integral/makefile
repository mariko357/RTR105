iterations.png: precision.dat plot plot-smooth
	./plot
	./plot-smooth

precision.dat: integral-precision.c
	gcc -lm integral-precision.c
	./a.out > precision.dat
	rm a.out