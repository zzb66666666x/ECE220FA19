#include<stdio.h>
/* provide swap function prototype here */
void swap(int * px, int *py);

int main()
{
    /* complete main function to demonstrate the use of swap */
	int x = 5;
	int y = 1;
	int* px = &x;
	int* py = &y;
	printf("the x y value should be %d %d \n", x,y);
	swap(px,py);
	printf("the x y value should be %d %d \n", x,y);
}


void swap (int * px, int * py)
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

