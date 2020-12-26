/* compute a function */

/* use sin() function from math.h */
/* type 'man sin' in your terminal to see instructions about sin() */

#include <stdio.h>
#include <math.h>
#define pi M_PI
int main()
{
    /* declarte variables */
	int n; double w1; double w2;
	double xi; double f_xi;
    /* prompt user for input */
	printf("Please enter the relavant variables including n, w1, w2:\n");
    /* get user input */
	scanf("%d,%lf,%lf",&n,&w1,&w2);
    /* for i from 0 to n(?) */
       /* compute and print x_i and f(x_i) */
	for (int i=0; i<=n-1; i++){
		xi = (i*pi)/(n-1);
		f_xi = sin(w1*xi) + 0.5*sin(w2*xi);
		printf("%lf,%lf\n",xi,f_xi);
	}
    /* exit the program */
    return 0;
}

