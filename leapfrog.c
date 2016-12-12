void leapfrog(double y[], double f[], int n, double t, double h, double yout[], 
	void (*fun)(double, double [], double [])) {
 
	int i;
	for (i=1;i<=n;i+=2) {
	y[i+1]=y[i+1]+h/2*f[i+1]; //kick
	y[i]=y[i]+h*y[i+1]; //drift
	} 
	fun(t,y,f); //call the function
	for (i=1;i<=n;i+=2) {
	yout[i]=y[i];
	yout[i+1]=y[i+1]+h/2*f[i+1]; //re-sync
		
	}

}

