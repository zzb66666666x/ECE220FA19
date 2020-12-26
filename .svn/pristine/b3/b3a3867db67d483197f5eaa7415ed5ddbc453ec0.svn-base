#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Intro paragraph
This program calculates the roots of a polynomial by the Newton method.
Before applying the Newton method, the Budan's method is implemented to determine the upper bound of the number of roots.
As for the Newton method, this programs picks the improved version of it called Halley's method.
When calculating the result, this programs picks staring points from the interval uniformly with a mesh-size 0.5 to make sure that every root will be found.
*/
/* function prototypes */
double abs_double(double y);
double fx_val(double a, double b, double c, double d, double e, double x);
double fx_dval(double a, double b, double c, double d, double e, double x);
double fx_ddval(double a, double b, double c, double d, double e, double x);
double newrfind_halley(double a, double b, double c, double d, double e, double x);
int rootbound(double a, double b, double c, double d, double e, double r, double l);
int hasRoot = 0;										/* a flag to tell if there are roots */
int iter_limit = 10000;									/* some constants */
double val_limit = 0.000001;

int main(int argc, char **argv)
{
    double a, b, c, d, e, l, r;
    FILE *in;

    if (argv[1] == NULL) 
    {
        printf("You need an input file.\n");
        return -1;
    }

    /* this code reads input from a file  -- do not modify it! */
    in = fopen(argv[1], "r");
    if (in == NULL)
        return -1;

    fscanf(in, "%lf", &a);
    fscanf(in, "%lf", &b);
    fscanf(in, "%lf", &c);
    fscanf(in, "%lf", &d);
    fscanf(in, "%lf", &e);
    fscanf(in, "%lf", &l);
    fscanf(in, "%lf", &r);

    fclose(in);
    
    /* The values are read into the variable a, b, c, d, e, l and r.
       You have to find the bound on the number of roots using rootbound function.
       If it is > 0 try to find the roots using newrfind function.
       You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.  */
    
    /* write tour code here */
	/* variables */
	int upbound;
	double start_point = l;
	double new_root;
	upbound = rootbound(a,b,c,d,e,r,l);					/* I will first determine the number of roots. */
	if (upbound == 0){									/* There are no roots in the interval by Budan's algorithm. */
		printf("The polynomial has no roots in the given interval.\n");
	}
	else{
		while (start_point <= r){						/* Pick staring points. */
			new_root = newrfind_halley(a,b,c,d,e,start_point);
			if (hasRoot && (new_root > l) && (new_root < r)){
				printf("Root found: %lf\n",new_root);	/* Find one root from one specific starting point. */
				hasRoot = 0;							/* Update the flag. */
			}
			else{
				hasRoot = 0;							/* no roots */
				printf("No roots found.\n");
			}
			start_point += 0.5;
		}
	}

    return 0;
}

/* implement these functions */

double abs_double(double y)
{
    /* Change this to return the absolute value of y i.e |y| */
	double ans;
	ans = (y >= 0 ? y : -1*y);							/* If the input is smaller than 0, the output will be the minus of it. */
    return ans;
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    /* Change this to return the value of the polynomial at the value x  */
	double ans;
	ans = a*pow(x,4) + b*pow(x,3) + c*pow(x,2) + d*pow(x,1) + e;
    return ans;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    /* Change this to return the value of the derivative of the polynomial at the value x */
	double ans;											/* calculate the derivative */
	ans = 4*a*pow(x,3) + 3*b*pow(x,2) + 2*c*pow(x,1) + d;
    return ans;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
	double ans;											/* second order derivative */
	ans = 12*a*pow(x,2) + 6*b*pow(x,1) + 2*c;
    return ans;
}

double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    /* Change this to return the root found starting from the initial point x using Halley's method */
	double ans;
	double xnew,xcur,fx_cur,dfx_cur,ddfx_cur,fx_new;
	int iteration = 0;
	xcur = x;
	while (iteration < iter_limit){
		fx_cur = fx_val(a,b,c,d,e,xcur);				/* calculate some f values */
		dfx_cur = fx_dval(a,b,c,d,e,xcur);
		ddfx_cur = fx_ddval(a,b,c,d,e,xcur);
		xnew = xcur - (2*fx_cur*dfx_cur)/(2*pow(dfx_cur,2) - fx_cur*ddfx_cur);
		fx_new = fx_val(a,b,c,d,e,xnew);
		if (abs_double(fx_new - fx_cur) < val_limit){	/* No obvious changes in result for each iteration */
			/* root found */
			hasRoot = 1;								/* New root found. */
			break;
		}
		else{
			iteration++;
			xcur = xnew;
		}
	}
	ans = xcur;
    return ans;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{	/* This function implements the Budan's method. */
    /* Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r). */
	int ans = 0;
	int i;
	int vl = 0;
	int vr = 0;
	double al[5];	
	double ar[5];
	double al_nonzero[5]={0};
	double ar_nonzero[5]={0};
	int al_pointer = 0;
	int ar_pointer = 0;									/* the calculation of coeffients of functions including f(x+r) and f(x+l) */
	/* x^4 */
	al[0] = a;	ar[0] = a;	
	/* x^3 */									
	al[1] = 4*a*l + b;	
	ar[1] = 4*a*r + b;		
	/* x^2 */				
	al[2] = 6*a*l*l + 3*b*l + c;	
	ar[2] = 6*a*r*r + 3*b*r + c;
	/* x */
	al[3] = 4*a*pow(l,3) + 3*b*l*l + 2*c*l + d;
	ar[3] = 4*a*pow(r,3) + 3*b*r*r + 2*c*r + d;
	/* constant */
	al[4] = a*pow(l,4) + b*pow(l,3) + c*l*l + d*l + e;
	ar[4] = a*pow(r,4) + b*pow(r,3) + c*r*r + d*r + e;	
	for (i = 0; i<5; i++){
		if (al[i] != 0){								/* eliminating zeros in the array */
			al_nonzero[al_pointer] = al[i];
			al_pointer++;
		}
		if (ar[i] != 0){
			ar_nonzero[ar_pointer] = ar[i];
			ar_pointer++;
		}			
	}
	/* calculating ans */
	for (i = 1; i<al_pointer; i++){
		if (al_nonzero[i]*al_nonzero[i-1] < 0){			/* Identify one change in the signs. */
			vl++;										/* Increment the vl. */
		}
	}
	for (i = 1; i<ar_pointer; i++){
		if (ar_nonzero[i]*ar_nonzero[i-1] < 0){
			vr++;	
		}	
	}
	ans = abs(vl-vr);
    return ans;
}

