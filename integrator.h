
void euler(double y[], double f[], int n, double x, double h, double yout[],void (*fun)(double, double [],double []));
void leapfrog(double y[], double f[], int n, double x, double h, double yout[], void (*fun)(double, double [], double []));
void rk4(double y[], double f[], int n, double x, double h, double yout[],void (*fun)(double, double [],double []));
