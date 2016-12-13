all: init galaxy kevans

init:
	gcc -o init Initialconditions.c nrutil.c -O0 -lm

kevans:
	gcc -o kevans IC_Kevans.c nrutil.c -O0 -lm

galaxy:
	gcc -o galaxy Nbody_galaxy.c nrutil.c leapfrog.c rk4.c -O0 -lm

clean:
	rm -f init kevans galaxy *.o
