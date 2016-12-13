#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "integrator.h"
#define FILENAME "xy.dat"
#define N 1000
#define iter 1
#define M 100
#define freq 2
#define h 0.36
#define P 7.29

void fun(double t,double yf[],double f[]) {
	double xij,yij,zij,rij3,axij,ayij,azij,rij;
	int i,j;
	i=1;
	j=1;
	xij=0.0;
	yij=0.0;
	zij=0.0;
	axij=0.0;
	ayij=0.0;
	azij=0.0;	
	
	for (i=1;i<=N;i++) {
		f[1+(i-1)*6]=yf[2+(i-1)*6];
        	f[3+(i-1)*6]=yf[4+(i-1)*6];
        	f[5+(i-1)*6]=yf[6+(i-1)*6];
	        f[2+(i-1)*6]=0.0;
        	f[4+(i-1)*6]=0.0;   
        	f[6+(i-1)*6]=0.0;

	for (j=1;j<=N;j++) {
		if (j!=i) {
			xij=yf[1+(i-1)*6]-yf[1+(j-1)*6];
			yij=yf[3+(i-1)*6]-yf[3+(j-1)*6];
			zij=yf[5+(i-1)*6]-yf[5+(j-1)*6];
			rij=sqrt((xij*xij)+(yij*yij)+(zij*zij));
			axij=-1.0*M*xij/pow(rij,3);
			ayij=-1.0*M*yij/pow(rij,3);
			azij=-1.0*M*zij/pow(rij,3);
	
			f[2+(i-1)*6]+=axij;
        		f[4+(i-1)*6]+=ayij;
        		f[6+(i-1)*6]+=azij;
			}
		}
	}
}
int main(int argc, char *argv[]) {
/* Here, we initialize the variables. */
	FILE * foo;
	FILE * galaxy_rk4;
	FILE * galaxy_lf;
	foo=fopen(FILENAME,"r");
	galaxy_rk4=fopen("galaxy_rk4.dat","w");
	galaxy_lf=fopen("galaxy_lf.dat","w");
	double *yf,*f;
	double x,y,z,vx,vy,vz;
	double t,T,r,E;
	double xij,yij,zij,vxij,vyij,vzij,integrator,vdotr,v;
	int n,i,j,a;
	n=6*N;
/* Here we assign our vectors */
	yf=dvector(1,n);
	f=dvector(1,n);
/* Initialize other variables */
        t=0.0;
	T=P*iter;
	E=0.0;
	a=0;
	integrator=atoi(argv[1]);
/* This first for loop is used to pre-allocate the positions and
velocities with the initial conditions */
	for (i=1;i<=N;i++) {
		fscanf(foo,"%lf %lf %lf %lf %lf %lf",&x,&y,&z,&vx,&vy,&vz);
		yf[1+(i-1)*6]=x;
		yf[2+(i-1)*6]=vx;
		yf[3+(i-1)*6]=y;
		yf[4+(i-1)*6]=vy;
		yf[5+(i-1)*6]=z;
		yf[6+(i-1)*6]=vz;
		
		}
	for (i=1;i<=N;i++) {
		if (integrator==0) {
		fprintf(galaxy_rk4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1+(i-1)*6],yf[3+(i-1)*6],
                	yf[5+(i-1)*6],yf[2+(i-1)*6],yf[4+(i-1)*6],yf[6+(i-1)*6]);
		}
		if (integrator==1) {
                fprintf(galaxy_lf,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1+(i-1)*6],yf[3+(i-1)*6],
                        yf[5+(i-1)*6],yf[2+(i-1)*6],yf[4+(i-1)*6],yf[6+(i-1)*6]);
                }
	}

/* Now we can integrate using Leapfrog and RK4 */
	for (t=0;t<=T;t+=h) {
		printf("The time is %lf\n",t);
		if (integrator==0) {
			a+=1;
			fun(t,yf,f);
			rk4(yf,f,n,t,h,yf,fun);
			if (a==freq) {
			for (i=1;i<=N;i++) {
			//printf("Count is %lf",a);
			fprintf(galaxy_rk4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1+(i-1)*6],yf[3+(i-1)*6],
                        	yf[5+(i-1)*6],yf[2+(i-1)*6],yf[4+(i-1)*6],yf[6+(i-1)*6]);
			}
			a=0;
			}
		}
		else if (integrator==1) {
			a+=1;
			fun(t,yf,f);
			leapfrog(yf,f,n,t,h,yf,fun);
                        if (a==freq) {
                        for (i=1;i<=N;i++) {
                        fprintf(galaxy_lf,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1+(i-1)*6],yf[3+(i-1)*6],
                        	yf[5+(i-1)*6],yf[2+(i-1)*6],yf[4+(i-1)*6],yf[6+(i-1)*6]);
			}
			a=0;
			}
		}
		else {printf("Invalid input: only 0 or 1 allowed.");}
	}
	free_dvector(f,1,N);
	free_dvector(yf,1,N);
	fclose(foo);
	fclose(galaxy_rk4);
	fclose(galaxy_lf);

}
