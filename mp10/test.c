#include <stdio.h>


#include "cmp_mat.h"
#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

int main(int argc, char *argv[]){
    if(argc > 2){
        printf("Too many arguments.\n");
        return 0;
    }
    if (argc == 2){
        int s = atoi(argv[1]);
        switch (s){
            case 1:
                printf("Test 1: tuple functions\n");
                goto TEST_1;
                break;
            default:
                printf("Error: Valid arguments are 1-3");
                return 0;
        }        
        printf("%s\n",argv[1]);
    }


	TEST_1:printf("calling load_tuples on \"matrices/input_mats/scrambled_rows.txt\":\n");
	sp_tuples * unscrambledrowst = load_tuples("matrices/input_mats/scrambled_rows.txt");
	printt(unscrambledrowst);

	destroy_tuples(unscrambledrowst);

	return 0;
}
