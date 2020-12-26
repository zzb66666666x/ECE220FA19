/***************************
 *  * pgm.c
 *   ***************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"

#define ARRAY_SIZE 10

int main(void)
{
    char a[ARRAY_SIZE] = {'g','d','i','b','f','h','j','a','c','e'};
						 //0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9
    BTREE root;

    root = create_tree(a, 0, ARRAY_SIZE) ;
    assert(root != NULL);

    printf("PREORDER\n");
    preorder(root);
    printf("\n");

    printf("INORDER\n");
    inorder(root);
    printf("\n");

    printf("POSTORDER\n");
    postorder(root);
    printf("\n");
	
	return 0;
}

