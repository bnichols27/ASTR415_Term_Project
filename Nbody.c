#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nrutil.h"
#include "integrator.h"
#define FILENAME "Nbody_init.dat"
#define N 2
#define iter 100
#define m 1.0
#define freq 5
#define h 0.05
#define P 2.42

void fun(double t,double yf[],double f[]) {
	//printf("Function called\n");
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
			axij=-1.0*m*xij/pow(rij,3);
			ayij=-1.0*m*yij/pow(rij,3);
			azij=-1.0*m*zij/pow(rij,3);
	
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
	FILE * pos_rk4;
	FILE * vel_rk4;
	FILE * pos_lf;
        FILE * vel_lf;
	foo=fopen(FILENAME,"r");
	pos_rk4=fopen("pos_rk4.dat","w+");
	vel_rk4=fopen("vel_rk4.dat","w+");
	pos_lf=fopen("pos_lf.dat","w+");
	vel_lf=fopen("vel_lf.dat","w+");
	double *yf,*f;
	double x,y,z,vx,vy,vz;
	double t,T,r,v1_sq,v2_sq,E;
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
		//printf("%d\n",N);
		fscanf(foo,"%lf %lf %lf %lf %lf %lf",&x,&y,&z,&vx,&vy,&vz);
		yf[1+(i-1)*6]=x;
		yf[2+(i-1)*6]=vx;
		yf[3+(i-1)*6]=y;
		yf[4+(i-1)*6]=vy;
		yf[5+(i-1)*6]=z;
		yf[6+(i-1)*6]=vz;
		
		}
	if (integrator==0) {
	fprintf(pos_lf,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1],yf[3],
                yf[5],yf[7],yf[9],yf[11],E);
	}
	if (integrator==1) {
	fprintf(pos_rk4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1],yf[3],
                yf[5],yf[7],yf[9],yf[11],E);
	}
/* Now we can integrate using Leapfrog */
	for (t=0;t<=T;t+=h) {		
		a+=1;
		fun(t,yf,f);
		if (integrator==0) {
			rk4(yf,f,n,t,h,yf,fun);
			xij=yf[1]-yf[7];
                	yij=yf[3]-yf[9];
                	zij=yf[5]-yf[11];
			vxij=yf[2]-yf[8];
                        vyij=yf[4]-yf[10];
                        vzij=yf[6]-yf[12];
			r=sqrt(xij*xij+yij*yij+zij*zij);
			v1_sq=yf[2]*yf[2]+yf[4]*yf[4]+yf[6]*yf[6];
			vdotr=vxij*xij+vyij*yij+vzij*zij;
			v2_sq=yf[8]*yf[8]+yf[10]*yf[10]+yf[12]*yf[12];
			v=vdotr/r;
			E=0.5*v1_sq+0.5*v2_sq-1/r;
			if (a==freq) {
				fprintf(vel_rk4,"%lf %lf\n",v,r);
				fprintf(pos_rk4,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1],yf[3],yf[5],yf[7],
                        		yf[9],yf[11],E);
				a=0;
			}
		}
		else if (integrator==1) {
			leapfrog(yf,f,n,t,h,yf,fun);
			xij=yf[1]-yf[7];
                        yij=yf[3]-yf[9];
                        zij=yf[5]-yf[11];
			vxij=yf[2]-yf[8];
                        vyij=yf[4]-yf[10];
                        vzij=yf[6]-yf[12];
                        r=sqrt(xij*xij+yij*yij+zij*zij);
                        v1_sq=yf[2]*yf[2]+yf[4]*yf[4]+yf[6]*yf[6];
                        v2_sq=yf[8]*yf[8]+yf[10]*yf[10]+yf[12]*yf[12];
			vdotr=vxij*xij+vyij*yij+vzij*zij;
			v=vdotr/r;
                        E=0.5*v1_sq+0.5*v2_sq-1/r;
			if (a==freq){
				fprintf(vel_lf,"%lf %lf\n",v,r);
                                fprintf(pos_lf,"%lf %lf %lf %lf %lf %lf %lf %lf\n",t,yf[1],yf[3],yf[5],yf[7],
                                        yf[9],yf[11],E);
                                a=0;
                        }	
		}
		else {printf("Invalid Input: Only 0 or 1 allowed.");}
	}
	
	
	free_dvector(f,1,N);
	free_dvector(yf,1,N);
	fclose(vel_rk4);
	fclose(pos_rk4);
	fclose(vel_lf);
	fclose(pos_lf);
}
