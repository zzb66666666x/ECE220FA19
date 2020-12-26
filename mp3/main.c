#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Write your code under the two if statements indicated below. */
int main(int argc, char **argv)
{
    double omega1, omega2, omegac, T, dt;
    int N, method;
    FILE *in;

    int i;
    double Voutnew = 0.0, Voutcur = 0.0, Voutprev = 0.0;
    /* If implementing method 2 for challenge, declare additional variables here */
    double Voutnew2 = 0.0, Voutcur2 = 0.0;
    int j;   
    /* Open the file and scan the input variables */
    if (argv[1] == NULL) 
    {
        printf("You need an input file.\n");
        return -1;
    }

    if ((in = fopen(argv[1], "r")) == NULL)
    {
        printf("Unable to open specified file %s\n", argv[1]);
        return -1;
    }

    fscanf(in, "%lf", &omega1);
    fscanf(in, "%lf", &omega2);
    fscanf(in, "%lf", &omegac);
    fscanf(in, "%d", &method);

    fclose(in);

    T = 3 * 2 * M_PI / omega1; 	        /* Total time */
    N = 20 * T / (2 * M_PI / omega2);   /* Total number of time steps */
    dt = T / N;                         /* Time step ("delta t") */
    double Vout[N];						/* Use one array to save all the data */
    Vout[0] = Voutnew;					/* Initialize the first element in the array to be 0 */
    /* Method number 1 corresponds to the finite difference method */
    if (method == 1) 
    {
        /* Write your code here! */
	int prev_index;
	double temp1 = 1/(sqrt(2)*dt*omegac);
	double temp2 = 1/(dt*dt*omegac*omegac);
	for (i=0;i<=N-1;i++ ){				/* The i is the index of each Vin */
		Voutprev = Voutcur;				/* Use the interation to update the variables */
		Voutcur = Voutnew;	
		prev_index = i-1;				/* If the index < 0, then set the Voutprev to be 0 */
		if (prev_index < 0){Voutprev = 0;}
		/* Since n begins with 0 and the first value calculated by this formula should be Vout[1]. Vout[0] has been set to 0 already */
		Voutnew = (1/(temp1 + temp2))*((2*temp2-1)*Voutcur + (temp1-temp2)*Voutprev + sin(omega1*i*dt) + 0.5*sin(omega2*i*dt));
		/* Below is some code for testing */
		/*printf("Voutprev is %lf   ",Voutprev);
		printf("Voutcur is %lf   ",Voutcur);
		printf("Voutnew is %lf   ",Voutnew);
		printf("\n");*/
		if (i != N-1){					/* Judge whether the it's the last element in the array */
			Vout[i+1] = Voutnew;
		}
	}
    }

    /* Method number 2 corresponds to the Runge-Kutta method (only for challenge). */
    else if (method == 2) 
    {
    /* Write your code here for the challenge problem. */
	double k1,k2,k3,k4,m1,m2,m3,m4;
	for (j=0; j<=N-1; j++){
		/* Below is the code to calculate some temporary values for Vout1 */
		k1 = Voutcur2; 					/* Calculate k1 */
		k2 = Voutcur2 + (k1*dt)/2; 		/* Calculate k2 */
		k3 = Voutcur2 + (k2*dt)/2; 		/* Calculate k3 */
		k4 = Voutcur2 + k3*dt;			/* Calculate k4 */
		/* Implement the calculation of Vout */
		Voutnew = Voutcur + (dt/6)*(k1 + 2*k2 + 2*k3 + k4);
		/* Below is the code for some temporary values for Vout2 */
		m1 = (omegac*omegac)*(sin(omega1*j*dt)+0.5*sin(omega2*j*dt)-Voutcur)-omegac*sqrt(2)*Voutcur2;	/* Calculate m1 */
		m2 = m1*(1+dt/2); 				/* Calculate m2 */
		m3 = m1 + (m2*dt)/2; 			/* Calculate m3 */
		m4 = m1 + m3*dt;				/* Calculate m4 */
		/* Implement the calculation of Vout2 */
		Voutnew2 = Voutcur2 + (dt/6)*(m1 + 2*m2 + 2*m3 + m4);
		if (j != N-1){
			Vout[j+1] = Voutnew;		/* Save the result into memory */
		}
		Voutcur = Voutnew;				/* Update Voutcur */
		Voutcur2 = Voutnew2;			/* Update Voutcur2 */
	}	
    }

    else 
    {
        printf("Incorrect method number.\n");
        return -1;
    }
	
    /* Below is the code for printing out the results previous stored in the memory (array of Vout) */
    for (int j=0;j<=N-1;j++){
    	printf("%lf\n",Vout[j]);
    }

    return 0;
}
