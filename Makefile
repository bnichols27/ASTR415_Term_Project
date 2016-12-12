all:  Nbody Nbody_e9 

Nbody:
	gcc -o Nbody Nbody.c leapfrog.c rk4.c euler.c nrutil.c -O0 -lm
Nbody_e9:
	gcc -o Nbody_e9 Nbody_e9.c leapfrog.c rk4.c  nrutil.c -O0 -lm
clean:
	rm -f Nbody Nbody_e9 *.o
