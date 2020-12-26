#include <stdio.h>

int main() 
{
     int x, y, z;

     scanf("%d %d", &x, &y);

     z = foo1(&x, &y); /* z = x*y; */

     printf("z = %d\n", z);
 
     return 0; /* implement this with HALT */
}
 
int foo1(int *x, int *y) 
{/*pointer vaiable is the one that stored the address*/
    int total=0;

    for (; *x > 0; *x = *x - 1) {	/* the y is a pointer variable */
        total = foo2(total, *y);	/* pass a pointer means passing*/
    }								/* the actual address of y     */

    return total;
}
 
int foo2(int currentTotal, int y) 
{
    return currentTotal + y;
}

/*
5*4 gets transferred into 
0+4+4+4+4+4
5-1-1-1-1-1
*/
