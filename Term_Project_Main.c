/*UMD ASTR415 Term Project: Evans, Anand, Nichols*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "./nr.h"
#include "./nrutil.h"

float randR(float min, float max)
{
  return min + (float) (rand() / (float) (RAND_MAX) * (max - min));
}

int main() 
{
  char xy[20];

 sprintf(xy,"xy.dat");

FILE* xy_f = fopen(xy, "w");
 float i;
 for(i =1;i<=500;i++)
 {
	float u = randR(0,1);
	float v = randR(0,1);
	float x = sqrtf(-2*log(u));
	float y = sqrtf(-2*log(v));
	
	fprintf(xy_f,"%f %f \n" , x,y);
  }

return 0;
}
