#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
int main()
{
    char *p = (char*)malloc(sizeof(char)*10);
//printf("the value of pointer p originally is %p\n",p);
    /* Assign some value to p */
//p = "hello" will make the pointer point to a global const char which is not in the heap
    char temp[] = "hello";
	memcpy(p,temp,6);
    char *name = (char*)malloc(sizeof(char)*11);
//printf("the value of pointer name originally is %p\n",name);
    /* Assign some value to name */
    char temp2[] = "Bye";
	memcpy(name,temp2,4);
//printf("the value of p is %p\n",p);
//printf("the value of name is %p\n",name);
    memcpy(p, name,sizeof(char)*10); /* Problem begins here */
	free(p);
	free(name);
    return 0;
}


