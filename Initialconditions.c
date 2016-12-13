#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "nrutil.h"
#include "nr.h"
#define k 50
#define l 1
#define sq(x) x*x

double randR(double min, double max) {
        return min + (double) (rand()/ (double)(RAND_MAX)*(max-min));
        }
int main() {

        double m,u,v,x,y,z,p_r;
	double xshift,yshift;
        double R,A,vel,vx,vy,vz;
	double shift[2];
	double zheight[2];
        int i,j,N,n,counter;
        double r,r_eqn;
        char xy[20];
	shift[0]=-1.0;
	shift[1]=1.0;
	zheight[0]=0.4;
	zheight[1]=0.0;
        N=500;
	//R=1.0;
       	R=27.0;
        A=M_PI*R*R;
        counter=0;
        sprintf(xy,"xy.dat");
        FILE * xy_f=fopen(xy,"w+");
	for (j=0;j<2;j++) {
        	while(counter<=499) {
                	u=randR(-1*k,1*k);
                	v=randR(-1*k,1*k);
                	x=l*(sqrt(-2*log(u))-1);
                	y=l*(sqrt(-2*log(v))-1);
			xshift=x+shift[j];
			yshift=y+shift[j];
                	z=zheight[j]*x;
                	r=sqrt(sq(x)+sq(y));
                	p_r=exp(-r);
                	r_eqn=sq(x)+sq(y);
                	vel=shift[j]*sqrt(p_r*A/r);
			vx=v*(x/r);
			vy=v*(y/r);
                	vz=0;
                if (r_eqn<=sq(R)){
                        fprintf(xy_f,"%f %f %f %f %f %f %f\n",xshift,yshift,z,vx,vy,vz,r);
                        counter+=1;
                        }
                }
		counter=0;
	}
}
